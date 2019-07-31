/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 12:20:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		sh_close_all_other_contexts(t_context *context, t_list *contexts)
{
	t_context	*current_context;
	t_list		*ptr;

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
	reset_signals();
	sh_close_all_other_contexts(context, contexts);
	ret = context->builtin(context);
	exit(ret);
}

void		sh_execute_child_binary(t_context *context, t_list *contexts)
{
	sh_process_execute_dup_pipes(context);
	reset_signals();
	sh_close_all_other_contexts(context, contexts);
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	sh_process_execute_close_pipes(context);
	if (sh_verbose_exec())
		ft_dprintf(2, "Execve failed\n");
	exit(FAILURE);
}

void		sh_execute_child(t_context *context, t_list *contexts)
{
	if (context->builtin)
		sh_execute_child_builtin(context, contexts);
	else
		sh_execute_child_binary(context, contexts);
}
