/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:36:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/23 11:12:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
	//		ft_printf("SHIFT\n");
			if (sh_process_shift(action.action_union.state, parser))
				return (1);
		}
		else if (action.action_enum == REDUCE)
		{
	//		ft_printf("REDUCE\n");
			if (sh_process_reduce(action.action_union.production, parser))
				return (1);
		}
		else if (action.action_enum == ACCEPT)
		{
			// sh_print_parser_state(parser);
			return (0);
		}
		else if (action.action_enum == ERROR)
		{
	//		ft_printf("ERROR\n");
			return (1);
		}
		i++;
	}
	return (0);
}
