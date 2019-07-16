/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence_execute.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/15 09:00:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			sh_process_execute_close_pipes_list(t_list *contexts)
{
	t_list		*ptr;
	t_context	*context;

	ptr = contexts;
	while (ptr != NULL)
	{
		context = (t_context *)ptr->content;	
		sh_process_execute_close_pipes(context);
		ptr = ptr->next;
	}
}

int				sh_process_pipe_exec_fork(t_list *contexts)
{
	t_list		*ptr;
	t_context	*context_iter;

	ptr = contexts;
	while (ptr != NULL)
	{
		context_iter = (t_context *)ptr->content;
		if ((context_iter->pid = fork()) == -1)
		{
			sh_process_execute_close_pipes_list(contexts);
			return (FAILURE);
		}
		if (context_iter->pid == 0)
			sh_execute_child(context_iter, contexts);
		else
		{
			g_parent = context_iter->pid;
			ptr =  ptr->next;
		}
	}
	return (SUCCESS);
}

int				sh_process_pipe_sequence_execute(t_context *context,
					t_list *contexts)
{
	int			res;
	pid_t		wpid;
	int			res_save;

	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes_list(contexts);
		return (FAILURE);
	}
	if (sh_process_pipe_exec_fork(contexts) == FAILURE)
		return (FAILURE);
	sh_process_execute_close_pipes_list(contexts);
	while ((wpid = wait(&res)) > 0)
	{
		if (wpid == g_parent)
			res_save = res;
	}
	sh_env_update_exit_status(context, EXIT_STATUS(res_save));
	g_parent = 0;
	if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	return (SUCCESS);
}

int				sh_traverse_pipe_sequence_execute(t_ast_node *node,
		t_context *context)
{
	int ret;

	node->metadata.pipe_metadata.contexts = NULL;
	if (ft_lstlen(node->children) == 1)
	{
		context->current_pipe_sequence_node = NULL;
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		context->current_pipe_sequence_node = node;
		if ((ret = sh_traverse_tools_browse(node, context)) != SUCCESS)
			return (ret);
		return (sh_process_pipe_sequence_execute(context, node->metadata.
					pipe_metadata.contexts));
	}
}
