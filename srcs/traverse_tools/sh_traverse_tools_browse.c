/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_browse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:06:49 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/16 12:07:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_tools_browse(t_ast_node *node, t_context *context)
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
	return (SUCCESS);
}
