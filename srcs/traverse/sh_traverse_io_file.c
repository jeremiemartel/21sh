/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/22 12:48:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_io_file(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;

	child = (t_ast_node *)node->children->content;
	if (g_grammar[child->symbol->id].traverse(node, context) == FAILURE)
		return (FAILURE);
	node->children = node->children->next;
	return (sh_traverse_tools_browse(node, context));
	(void)node;
	(void)context;
}
