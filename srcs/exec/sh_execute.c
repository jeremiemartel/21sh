/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/20 07:51:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t g_parent;

int			sh_process_process_execute(t_context *context)
{
	int			res;

	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	if ((g_parent = fork()) == -1)
		return (FAILURE);
	if (g_parent == 0)
		sh_execute_child_binary(context, NULL);
	else
	{
		wait(&res);
		g_parent = 0;
		sh_env_update_ret_value_fork_result(context, res);
		sh_process_execute_close_pipes(context);
		if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
		{
			return (sh_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
		}
		g_glob.command_line.interrupted = WIFSIGNALED(res);
	}
	return (SUCCESS);
}

int			sh_add_to_pipe_sequence(t_context *context)
{
	t_context	*context_dup;

	if (!(context_dup = t_context_dup(context)))
		return (FAILURE);
	if (ft_lstaddnew_ptr_last(&context->current_pipe_sequence_node->
		metadata.pipe_metadata.contexts, context_dup,
			sizeof(t_context)))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_process_execute(t_context *context)
{
	if (context->current_pipe_sequence_node)
		return (sh_add_to_pipe_sequence(context));
	else
		return (sh_process_process_execute(context));
}
