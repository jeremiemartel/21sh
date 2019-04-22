/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:17:04 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/22 12:47:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			res;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		res = g_grammar[child->symbol->id].traverse(child, context);
		if (res == FAILURE)
			return (FAILURE);
		if (child->symbol->id == sh_index(LEX_TOK_AND_IF) || child->symbol->id == sh_index(LEX_TOK_OR_IF))
		{
			if (res == -5)
				return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}
