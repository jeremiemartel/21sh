/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/19 11:30:54 by ldedier          ###   ########.fr       */
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
	if (ret == FAILURE || ret == STOP_CMD_LINE)
		return (ret);
	context->phase = E_TRAVERSE_PHASE_EXECUTE;
	ret = g_grammar[child->symbol->id].traverse(child, context);
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
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if ((ret = sh_process_traverse_list_redir_exec(child, context, &ptr)))
		{
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
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
		return (sh_traverse_tools_browse(node, context));
	else
		return (sh_traverse_list_redir_exec(node, context));
}
