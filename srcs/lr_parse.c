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

int		sh_lr_parse(t_lr_parser *parser)
{
	t_list		*ptr;
	t_token		*token;
	t_action	action;

	parser->stack = NULL;
	parser->current_state =  (t_state *)parser->states->content;
	while (parser->tokens)
	{
		ptr = ft_lstpop_node(&parser->tokens);
		token = (t_token *)ptr->content;
		action = parser->lr_tables[parser->current_state->index][token->token_id];
		if (action.action_enum == SHIFT)
		{
			ft_printf("SHIFT\n");
		}
		else if (action.action_enum == REDUCE)
		{
			ft_printf("REDUCE\n");

		}
		else if (action.action_enum == ACCEPT)
			return (0);
		else if (action.action_enum == ERROR)
			return (1);
		sh_print_parser_state(parser);
	}
	return (0);
}
