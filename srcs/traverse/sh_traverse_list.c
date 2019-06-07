/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 03:28:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_traverse_list_redir_exec(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		context->phase = E_TRAVERSE_PHASE_REDIRECTIONS;
		if (g_grammar[child->symbol->id].traverse(child, context) == FAILURE)
			return (FAILURE);
		context->phase = E_TRAVERSE_PHASE_EXECUTE;
		if (g_grammar[child->symbol->id].traverse(child, context) == FAILURE)
			return (FAILURE);
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
