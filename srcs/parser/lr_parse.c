/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:36:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/29 18:52:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_shift(int state_index, t_lr_parser *parser)
{
	t_token	*token;
	t_ast_builder	*ast_builder;

	token = ft_lstpop_ptr(&parser->tokens);
	if (!(ast_builder = sh_new_ast_builder(token,
			&parser->cfg.symbols[token->index])))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift"));
	if (ft_lstaddnew_ptr(&parser->stack, ast_builder, sizeof(t_ast_builder *)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift"));
	if (ft_lstaddnew(&parser->stack, &state_index, sizeof(int)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift"));
	return (SUCCESS);
}

int		sh_lr_parse(t_lr_parser *parser)
{
	t_token		*token;
	t_action	action;
	int			state_index;
	int			i;

	i = 0;
	ft_lstdel_value(&parser->stack);
	parser->stack = NULL;
	if (ft_lstaddnew(&parser->stack, &i, sizeof(int)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_lr_parse"));
	while (parser->tokens)
	{
		if (parser->stack == NULL)
			return (2);
		state_index = *(int *)parser->stack->content;
		token = (t_token *)parser->tokens->content;
		action = parser->lr_tables[state_index][token->index];
		if (action.action_enum == SHIFT)
		{
			if (sh_process_shift(action.action_union.state_index, parser))
				return (FAILURE);
		}
		else if (action.action_enum == REDUCE)
		{
			if (sh_process_reduce(action.action_union.production, parser))
				return (FAILURE);
		}
		else if (action.action_enum == ACCEPT)
		{
		//	t_token_free(token);
		//	free(parser->tokens);
		//	parser->tokens = NULL;
			return (SUCCESS);
		}
		else if (action.action_enum == ERROR)
			return (2);
//		sh_print_parser_state(parser);
	}
	return (2);
}
