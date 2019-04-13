/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:36:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 17:14:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
	return (res);
}

int		sh_process_shift(t_state *state, t_lr_parser *parser)
{
	t_token	*token;
	t_ast_builder	*ast_builder;

	token = ft_lstpop_ptr(&parser->tokens);
	if (!(ast_builder = sh_new_ast_builder(token,
			&parser->cfg.symbols[token->index])))
		return (1);
	if (ft_lstaddnew_ptr(&parser->stack, ast_builder, sizeof(t_ast_builder *)))
		return (1);
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	return (0);
}

int		sh_is_replacing(t_ast_builder *ast_builder)
{
	return (ast_builder->symbol->replacing == 1 ||
			sh_is_term(ast_builder->symbol));
}

int		sh_process_reduce(t_production *production, t_lr_parser *parser)
{
	int				length;
	t_state			*state;
	t_state			*state_from;
	t_list			*ast_builder_list;
	t_list			*replacing_ast_ptr;
	t_list			*ptr;
	t_ast_builder	*ast_builder;
	t_ast_builder	*new_ast_builder;

	ast_builder_list = NULL;
	length = ft_lstlen(production->symbols);
	replacing_ast_ptr = NULL;
	while (length)
	{
		if (!ft_lstpop_ptr(&parser->stack)) //state
			return (1);
		if (!(ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (1);
		ast_builder = (t_ast_builder *)ptr->content;
		if (ast_builder->symbol->relevant && ast_builder->node)
		{
			if (sh_is_replacing(ast_builder))
				replacing_ast_ptr = ptr;
			else
				ft_lstadd_last(&ast_builder_list, ptr);
		}
		else
		{
			if (ast_builder->node)
				free(ast_builder->node);
			free(ast_builder);
			free(ptr);
		}
		length--;
	}
	if (replacing_ast_ptr)
		parser->root = ((t_ast_builder *)replacing_ast_ptr->content)->node;
	while (ast_builder_list != NULL)
	{
		ast_builder = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr(&((t_ast_builder *)replacing_ast_ptr->
			content)->node->children, ast_builder->node, sizeof(t_ast_node *)))
			return (1);
	}
	state_from = (t_state *)parser->stack->content;
	state = parser->lr_tables[state_from->index]
		[production->from->id].action_union.state;
	if (replacing_ast_ptr == NULL)
	{
		if (!(new_ast_builder = sh_new_ast_builder_no_node(production->from)))
			return (1);
		if (ft_lstaddnew_ptr(&parser->stack, new_ast_builder, sizeof(t_ast_builder)))
			return (1);
	}
	else
	{
		((t_ast_builder *)replacing_ast_ptr->content)->symbol = production->from;
		ft_lstadd(&parser->stack, replacing_ast_ptr);
	}
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	return (0);
}

int		sh_lr_parse(t_lr_parser *parser)
{
	t_token		*token;
	t_action	action;
	t_state		*state;
	int			i;

	i = 0;
	parser->stack = NULL;
	if (ft_lstaddnew_ptr(&parser->stack, parser->states->content,
			sizeof(t_state *)))
		return (1);
	while (parser->tokens)
	{
		if (parser->stack == NULL)
			return (1);
		state = (t_state *)parser->stack->content;
		token = (t_token *)parser->tokens->content;
		action = parser->lr_tables[state->index][token->index];
		if (action.action_enum == SHIFT)
		{
			ft_printf("SHIFT\n");
			if (sh_process_shift(action.action_union.state, parser))
				return (1);
		}
		else if (action.action_enum == REDUCE)
		{
			ft_printf("REDUCE\n");
			if (sh_process_reduce(action.action_union.production, parser))
				return (1);
		}
		else if (action.action_enum == ACCEPT)
		{
			sh_print_parser_state(parser);
			return (0);
		}
		else if (action.action_enum == ERROR)
		{
			ft_printf("ERROR\n");
			return (1);
		}
		sh_print_parser_state(parser);
		i++;
	}
	return (0);
}
