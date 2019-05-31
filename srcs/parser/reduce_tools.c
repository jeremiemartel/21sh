/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:01:51 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/27 18:02:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_init_ast_node(t_ast_node *node,
			t_token *token, t_symbol *symbol, t_ast_node *relative)
{
	node->children = NULL;
	node->symbol = symbol;
	node->token = token;
	node->metadata.command_metadata.redirections = NULL;
	node->relative = relative;
}

void	sh_init_ast_nodes(t_ast_builder *ast_builder,
			t_token *token, t_symbol *symbol)
{
	sh_init_ast_node(ast_builder->ast_node,
		token, symbol, ast_builder->cst_node);
	sh_init_ast_node(ast_builder->cst_node,
		token, symbol, ast_builder->ast_node);
}

t_ast_builder	*sh_new_ast_builder_no_token(t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	if (!(res->ast_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res);
		return (NULL);
	}
	if (!(res->cst_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res);
		free(res->ast_node);
		return (NULL);
	}
	sh_init_ast_nodes(res, NULL, symbol);
	return (res);
}

t_ast_builder	*sh_new_ast_builder_no_node(t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	res->ast_node = NULL;
	return (res);
}

t_ast_builder	*sh_new_ast_builder(t_token *token, t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	if (!(res->ast_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res);
		return (NULL);
	}
	if (!(res->cst_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res->ast_node);
		free(res);
		return (NULL);
	}
	sh_init_ast_nodes(res, token, symbol);
	return (res);
}

int		sh_is_replacing(t_ast_builder *ast_builder)
{
	return (ast_builder->symbol->replacing == 1 || sh_is_term(ast_builder->symbol));
}
