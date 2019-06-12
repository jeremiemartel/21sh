/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 15:54:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int     sh_traverse_and_or_execute(t_ast_node *node, t_context *context)
{
	t_list      *ptr;
	t_ast_node  *child;
	int         ret;
	int         prev_symbol;

	prev_symbol = -1;
	ptr = node->children;
	while (ptr != NULL)
	{
		if (prev_symbol != 1 
			&& ((prev_symbol == sh_index(LEX_TOK_AND_IF) && context->ret_value)
				|| (prev_symbol == sh_index(LEX_TOK_OR_IF) 
					&& !context->ret_value)))
			break;
		child = (t_ast_node *)ptr->content;
		if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
			return (ret);
		if ((ptr = ptr->next))
		{
			prev_symbol = ((t_ast_node *)(ptr->content))->symbol->id;
			ptr = ptr->next;
		}
	}
	return (SUCCESS);
}

int			sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
		return (sh_traverse_and_or_execute(node, context));
	else
	{
		return (sh_traverse_tools_browse(node, context));
	}
}
