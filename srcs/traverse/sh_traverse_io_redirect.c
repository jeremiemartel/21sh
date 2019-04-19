/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:27:03 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/19 14:35:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_io_redirect(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	int			fd;

	child = (t_ast_node*)node->children->content;
	// Looking for the file descriptor to redirect, -1 means default value
	fd = -1;
	if (child->symbol->id == sh_index(LEX_TOK_IO_NUMBER))
	{
		fd = ft_atoi(child->token->value);
		if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
			return (FAILURE);
		child = (t_ast_node*)node->children->content;
	}
	context->father_id = fd;
	ft_dprintf(2, "traverse : io_redirect\n");
	return (sh_traverse_tools_browse(node, context));
}
