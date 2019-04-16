/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/16 12:06:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_default(t_ast_node *node, t_context *context)
{
	t_list *ptr;
	t_ast_node	*child;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if (g_grammar[child->symbol->id].traverse(child, context) == FAILURE)
			return (FAILURE);
		ptr = ptr->next;
	}
	// sh_print_symbol(node->symbol);
	// ft_printf("\n");
	return (SUCCESS);
}
