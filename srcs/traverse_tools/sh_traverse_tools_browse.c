/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_browse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:06:49 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/31 12:42:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_tools_browse:
**		Call successively all node childrens
**		It do not change the node->children value
*/

int		sh_traverse_tools_browse(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	ptr = node->children;
	ret = SUCCESS;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
			break ;
		ptr = ptr->next;
	}
	return (ret);
}
