/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 03:38:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/18 05:51:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_ast_node	*sh_new_node(t_token *token)
{
	t_ast_node *node;

	if (!(node = (t_ast_node *)malloc(sizeof(t_ast_node))))
		return (NULL);
	node->token = token;
	node->parent = NULL;
	node->children = NULL;
	return (node);
}

t_ast_builder	*sh_new_ast_builder(t_ast_node **node, t_symbol *symbol)
{
	t_ast_builder *ast_builder;

	if (!(ast_builder = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	ast_builder->node = *node;
	ast_builder->symbol = symbol;
	return (ast_builder);
}

int		sh_add_new_node(t_ast_node **node_ptr, t_ast_node *node)
{
	if (!*node_ptr)
		*node_ptr = node;
	else
	{
		node->parent = *node_ptr;
		if (ft_lstaddnew_ptr_last(&((*node_ptr)->children), node, sizeof(t_ast_node)))
			return (1);
	}
	return (0);
}
/*
t_ast_node **get_address_last_child(t_ast_node *node)
{
	t_list *ptr;

	ptr = node->children;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (&((t_ast_node *)(ptr->content)));
}
*/
