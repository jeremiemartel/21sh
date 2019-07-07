/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:11:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/03 17:11:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_token(t_ast_node *node, t_token **token)
{
	if (*token)
	{
		free((*token)->value);
		(*token)->value = NULL;
		free(*token);
		(*token) = NULL;
		node->relative->token = NULL;
	}
}

void	sh_free_ast_node(t_ast_node **node, int update)
{
	t_ast_node		*child;
	t_ast_builder	*builder;

	if (!*node)
		return ;
	if ((*node)->token)
		sh_free_token(*node, &(*node)->token);
	if ((*node)->symbol->id == sh_index(SIMPLE_COMMAND))
		ft_lstdel_value(&(*node)->metadata.command_metadata.redirections);
	else if ((*node)->symbol->id == sh_index(PIPE_SEQUENCE))
		ft_lstdel(&(*node)->metadata.pipe_metadata.contexts,
			sh_free_context_dup_lst);
	while ((*node)->children != NULL)
	{
		child = (t_ast_node *)ft_lstpop_ptr(&(*node)->children);
		sh_free_ast_node(&child, update);
	}
	if (update && (builder = (*node)->builder))
	{
		if (builder->ast_node == *node)
			builder->ast_node = NULL;
		else
			builder->cst_node = NULL;
	}
	free(*node);
	*node = NULL;
}

void	sh_free_parser_trees(t_lr_parser *parser)
{
	sh_free_ast_node(&parser->ast_root, 1);
	sh_free_ast_node(&parser->cst_root, 1);
}

void	sh_free_ast_builder(t_ast_builder *ast_builder)
{
	sh_free_ast_node(&ast_builder->ast_node, 0);
	sh_free_ast_node(&ast_builder->cst_node, 0);
	free(ast_builder);
}
