/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/14 12:48:47 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t g_parent;

void		sh_close_all_other_contexts(t_context *context, t_list *contexts)
{
	t_context *current_context;
	t_list *ptr;

	ptr = contexts;
	while (ptr != NULL)
	{
		current_context = (t_context *)ptr->content;
		if (current_context != context)
			sh_process_execute_close_pipes(current_context);
		ptr = ptr->next;
	}
}

void		sh_execute_child_builtin(t_context *context, t_list *contexts)
{
	int ret;

	sh_process_execute_dup_pipes(context);
	sh_close_all_other_contexts(context, contexts);
	signal(SIGINT, SIG_DFL);
	ret = context->builtin(context);
	exit(ret);
}

void		sh_execute_child_binary(t_context *context, t_list *contexts)
{
	sh_process_execute_dup_pipes(context);
	sh_close_all_other_contexts(context, contexts);
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	sh_process_execute_close_pipes(context);
	if (sh_verbose_exec())
		ft_dprintf(2, "Execve failed\n");
	exit(FAILURE);
}

void	sh_execute_child(t_context *context, t_list *contexts)
{
	if (context->builtin)
		sh_execute_child_builtin(context, contexts);
	else
		sh_execute_child_binary(context, contexts);
}

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
		sh_env_vars_update_question_mark(context, res);
		g_parent = 0;
		sh_process_execute_close_pipes(context);
		if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (sh_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
	}
	return (SUCCESS);
}

int			sh_add_to_pipe_sequence(t_context *context)
{
	t_context	*context_dup;

	if (!(context_dup = t_context_dup(context)))
		return (FAILURE);
	if (ft_lstaddnew_ptr_last(&context->current_pipe_sequence_node->
				metadata.pipe_metadata.contexts, context_dup, sizeof(t_context)))
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
