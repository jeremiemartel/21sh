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

int		sh_process_shift(t_state *state, t_lr_parser *parser)
{
	t_token	*token;

	token = ft_lstpop_ptr(&parser->tokens);
	if (ft_lstaddnew_ptr(&parser->stack,
			&parser->cfg.symbols[token->token_id], sizeof(t_symbol *)))
		return (1);
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	return (0);
}

int		sh_process_reduce(t_production *production, t_lr_parser *parser)
{
	int			length;
	t_state		*state;
	t_state		*state_from;

	length = ft_lstlen(production->symbols);
	while (length)
	{
		if (!ft_lstpop_ptr(&parser->stack))
			return (1);
		if (!ft_lstpop_ptr(&parser->stack))
			return (1);
		length--;
	}
	state_from = (t_state *)parser->stack->content;
	state = parser->lr_tables[state_from->index]
		[production->from->id].action_union.state;
	if (ft_lstaddnew_ptr(&parser->stack, production->from, sizeof(t_symbol *)))
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
	int i;

	i = 0;
	parser->stack = NULL;
	if (ft_lstaddnew_ptr(&parser->stack, parser->states->content,
			sizeof(t_state *)))
		return (1);
	while (parser->tokens)
	{
		sh_print_parser_state(parser);
		if (parser->stack == NULL)
			return (1);
		state = (t_state *)parser->stack->content;
		token = (t_token *)parser->tokens->content;
		action = parser->lr_tables[state->index][token->token_id];
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
		ft_printf("after action:\n");
		sh_print_parser_state(parser);
		i++;
	}
	return (0);
}
