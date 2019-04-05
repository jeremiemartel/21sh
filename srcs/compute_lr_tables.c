/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_tables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:49:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 15:06:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		sh_init_action(t_action *action)
{
	action->action_enum = ERROR;
}

t_action	**sh_create_tables(t_lr_parser *parser)
{
	t_action	**res;
	int			i;
	int			height;

	height = ft_lstlen(parser->states);
	if (!(res = (t_action **)malloc(height * sizeof(t_action *))))
		return (NULL);
	i = 0;
	while (i < height)
	{
		if (!(res[i] = (t_action *)malloc(NB_SYMBOLS * sizeof(t_action))))
		{
			while (--i)
				free(res[i]);
			free(res);
			return (NULL);
		}
		sh_init_action(res[i]);
		i++;
	}
	return (res);
}

void	sh_fill_reduce(t_state *state, t_item *item, t_lr_parser *parser)
{
	if (item->production->from == &parser->cfg.start_symbol
			&& (item->lookahead->id == END_OF_INPUT))
		parser->lr_tables[state->index][END_OF_INPUT].action_enum = ACCEPT;
	else
	{
		parser->lr_tables[state->index]
			[item->lookahead->id].action_enum = REDUCE;
		parser->lr_tables[state->index]
			[item->lookahead->id].action_union.production = item->production;
	}
}

void	sh_fill_tables_by_transition(t_state *state, t_transition *transition,
			t_lr_parser *parser)
{
		parser->lr_tables[state->index]
			[transition->symbol->id].action_enum = SHIFT;
		parser->lr_tables[state->index]
			[transition->symbol->id].action_union.state = transition->state;
}

void	sh_fill_tables_by_state(t_state *state, t_lr_parser *parser)
{
	t_list			*ptr;
	t_item			*item;
	t_transition	*transition;

	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (item->progress == NULL)
			sh_fill_reduce(state, item, parser);
		ptr = ptr->next;
	}
	ptr = state->transitions;
	while (ptr != NULL)
	{
		transition = (t_transition *)ptr->content;
		sh_fill_tables_by_transition(state, transition, parser);
		ptr = ptr->next;
	}
}

void	sh_fill_tables(t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;

	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		sh_fill_tables_by_state(state, parser);
		ptr = ptr->next;
	}
}

int		sh_compute_lr_tables(t_lr_parser *parser)
{
	if (!(parser->lr_tables = sh_create_tables(parser)))
		return (1);
	sh_fill_tables(parser);
	return (0);
}
