/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/14 12:24:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_traverse_list_redir_exec(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
		ret = g_grammar[child->symbol->id].traverse(child, context);
		if (ret == STOP_CMD_LINE)
			return (ERROR);
		if ((ptr = ptr->next))
			ptr = ptr->next;
		if (ret)
			continue;
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
