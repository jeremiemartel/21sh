/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:01:51 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 15:15:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_ast_builder	*sh_new_ast_builder_no_token(t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	if (!(res->node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res);
		return (NULL);
	}
	res->node->symbol = symbol;
	res->node->children = NULL;
	res->node->parent = NULL;
	res->node->token = NULL;
	return (res);
}

t_ast_builder	*sh_new_ast_builder_no_node(t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	res->node = NULL;
	return (res);
}

t_ast_builder	*sh_new_ast_builder(t_token *token, t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	if (!(res->node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res);
		return (NULL);
	}
	res->node->children = NULL;
	res->node->parent = NULL;
	res->node->token = token;
	res->node->symbol = symbol;
	return (res);
}

int		sh_is_replacing(t_ast_builder *ast_builder)
{
	return (ast_builder->symbol->replacing == 1 ||
			sh_is_term(ast_builder->symbol));
}
