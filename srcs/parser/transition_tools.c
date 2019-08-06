/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:51:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/27 16:57:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_is_eligible_for_transition(t_state *state, t_item *item)
{
	t_list *ptr;
	t_item *item_ptr;

	ptr = state->items;
	while (ptr != NULL)
	{
		item_ptr = (t_item *)ptr->content;
		if (item->production == item_ptr->production
				&& item->progress->next == item_ptr->progress)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

t_state			*sh_get_state_by_symbol(t_item *item, t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;

	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		if (sh_is_eligible_for_transition(state, item))
		{
			return (state);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

t_state			*sh_get_state_by_transition(t_state *state, t_symbol *symbol)
{
	t_list			*ptr;
	t_transition	*transition;

	ptr = state->transitions;
	while (ptr != NULL)
	{
		transition = (t_transition *)ptr->content;
		if (transition->symbol == symbol)
			return (transition->state);
		ptr = ptr->next;
	}
	return (NULL);
}

t_transition	*sh_new_transition(t_state *to, t_symbol *symbol)
{
	t_transition *res;

	if (!(res = (t_transition *)malloc(sizeof(t_transition))))
		return (NULL);
	res->state = to;
	res->symbol = symbol;
	return (res);
}

t_item			*sh_new_item_advance(t_item *item)
{
	t_item	*res;
	int		i;

	if (!(res = (t_item *)malloc(sizeof(t_item))))
		return (NULL);
	res->production = item->production;
	res->progress = item->progress->next;
	res->parsed = 0;
	i = 0;
	while (i < NB_TERMS)
	{
		res->lookaheads[i] = item->lookaheads[i];
		i++;
	}
	return (res);
}
