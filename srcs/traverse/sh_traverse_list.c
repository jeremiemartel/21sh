/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 13:40:12 by jmartel          ###   ########.fr       */
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
		if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
			return (ret);
		context->phase = E_TRAVERSE_PHASE_REDIRECTIONS;
		if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
			return (ret);
		context->phase = E_TRAVERSE_PHASE_EXECUTE;
		if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
			return (ret);
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
	return (SUCCESS);
}

int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
		return (sh_traverse_tools_browse(node, context));
	else
		return (sh_traverse_list_redir_exec(node, context));
	return (SUCCESS);
}
