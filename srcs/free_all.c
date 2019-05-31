/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/29 19:45:38 by ldedier          ###   ########.fr       */
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

void	sh_free_ast_node(t_ast_node **node)
{
	t_ast_node	*child;

	if (!*node)
		return ;
	if ((*node)->token)
		sh_free_token(*node, &(*node)->token);
	if ((*node)->symbol->id == sh_index(SIMPLE_COMMAND))
		ft_lstdel_value(&(*node)->metadata.command_metadata.redirections);
	while ((*node)->children != NULL)
	{
		child = (t_ast_node *)ft_lstpop_ptr(&(*node)->children);
		sh_free_ast_node(&child);
	}
	free(*node);
	*node = NULL;
}

void	sh_free_parser_trees(t_lr_parser *parser)
{
	sh_free_ast_node(&parser->ast_root);
	sh_free_ast_node(&parser->cst_root);
}

void	sh_free_ast_builder(t_ast_builder *ast_builder)
{
	sh_free_ast_node(&ast_builder->ast_node);
	sh_free_ast_node(&ast_builder->cst_node);
	free(ast_builder);
}

void	free_file(t_file *file)
{
	free(file->name);
	free(file->fullname);
	free(file);
}

void    free_file_dlst(void *f, size_t dummy)
{
	(void)dummy;
	free_file((t_file *)f);
}

void    free_state_lst(void *s, size_t dummy)
{
	(void)dummy;
	sh_free_state((t_state *)s);
}

void	sh_free_lr_automata(t_lr_parser *parser)
{
	ft_lstdel(&parser->states, free_state_lst);
}

void		sh_free_all(t_shell *shell)
{
	(void)shell;
}
