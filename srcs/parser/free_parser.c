/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:19:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/31 15:19:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_stack_item(t_stack_item *stack_item)
{
	if (stack_item->stack_enum == E_STACK_AST_BUILDER)
	{
		if (!stack_item->transfered_ast_builder)
			sh_free_ast_builder(stack_item->stack_union.ast_builder);
		else
			free(stack_item->stack_union.ast_builder);
	}
	free(stack_item);
}

void	sh_free_stack_item_lst(void *si, size_t dummy)
{
	(void)dummy;
	sh_free_stack_item((t_stack_item *)si);
}

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

void    free_state_lst(void *s, size_t dummy)
{
	(void)dummy;
	sh_free_state((t_state *)s);
}

void	sh_free_lr_automata(t_lr_parser *parser)
{
	ft_lstdel(&parser->states, free_state_lst);
}

void	sh_free_production(void *p, size_t dummy)
{
	t_production *production;

	(void)dummy;
	production = (t_production *)p;
	ft_lstdel_ptr(&production->symbols);
//	free(p);
}

void	sh_free_cfg(t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < NB_SYMBOLS)
	{
		ft_lstdel(&cfg->symbols[i].productions, sh_free_production);
		i++;
	}
	ft_lstdel(&cfg->start_symbol.productions, sh_free_production);
}

void	sh_free_parser(t_lr_parser *parser)
{
	int i;

	ft_lstdel(&parser->stack, sh_free_stack_item_lst);
	sh_free_parser_trees(parser);
	if (parser->lr_tables && parser->nb_states != -1)
	{
		i = 0;
		while (i < parser->nb_states)
		{
			free(parser->lr_tables[i]);
			i++;
		}
		free(parser->lr_tables);
	}
	ft_lstdel(&parser->tokens, sh_free_token_lst);
	sh_free_cfg(&parser->cfg);
}
