/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 20:10:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/06 20:10:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_ast_node *new_ast_node(t_symbol *symbol, char *value, int token_index)
{
	t_ast_node	*res;
	t_token		*token;

	token = NULL;
	if (value)
	{
		if (!(token = sh_new_token(token_index, value)))
			return (NULL);
	}
	if (!(res = malloc(sizeof(t_ast_node))))
	{
		t_token_free(token);
		return (NULL);
	}
	sh_init_ast_node(res, token, symbol, NULL);
	return (res);
}

int			add_to_ast_node(t_ast_node *node, t_symbol *symbol,
				char *value, int token_index)
{
	t_ast_node *new_node;

	if (!(new_node = new_ast_node(symbol, value, token_index)))
		return (1);
	if (ft_lstaddnew_ptr_last(&node->children, new_node,
		sizeof(t_ast_node *)))
	{
		sh_free_ast_node(&node, 0);
		return (1);
	}
	return (0);
}
