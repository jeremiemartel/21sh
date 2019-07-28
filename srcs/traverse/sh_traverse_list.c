/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/28 16:48:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_traverse_list_redir_exec(t_ast_node *child,
	t_context *context, t_list **ptr)
{
	int ret;

	context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (ret == STOP_CMD_LINE)
		return (ERROR);
	if ((*ptr = (*ptr)->next))
		*ptr = (*ptr)->next;
	if (ret)
		return (KEEP_READ);
	context->phase = E_TRAVERSE_PHASE_REDIRECTIONS;
	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (ret == FAILURE)
		return (FAILURE);
	if (ret == ERROR)
	{
		if (sh_env_update_question_mark(context->shell) == FAILURE)
			return (FAILURE);
		return (KEEP_READ);
	}
	context->phase = E_TRAVERSE_PHASE_EXECUTE;
	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (ret == STOP_CMD_LINE)
		return (ERROR);
	if (ret == FAILURE)
		return (ret);
	if (!context->shell->running)
		return (ret);
	return (SUCCESS);
}

static int	sh_traverse_list_redir_exec(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	ptr = node->children;
	if (sh_verbose_traverse())
		ft_dprintf(2,
		BLUE"traverse : execute : %s : start\n"EOC, node->symbol->debug);
	while (ptr != NULL && context->shell->running)
	{
		child = (t_ast_node *)ptr->content;
		if ((ret = sh_process_traverse_list_redir_exec(child, context, &ptr)))
		{
			if (sh_verbose_traverse())
				ft_dprintf(2, BLUE
				"traverse : execute : LIST : returned value : %d\n"EOC, ret);
			if (ret == KEEP_READ)
				continue ;
			else
				return (ret);
		}
	}
	return (SUCCESS);
}

int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE
			"traverse : interactive_redirections : LIST : start\n"EOC);
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		ret = sh_traverse_list_redir_exec(node, context);
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE
			"traverse : execute : LIST : returned value : %d\n"EOC, ret);
		return (ret);
	}
}
