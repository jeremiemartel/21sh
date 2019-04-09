/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_automata.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:39:13 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/04 20:11:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** returns if 'state' should be the destination of the transition of a state
** containing the item 'item'
*/

int		sh_is_eligible_for_transition(t_state *state, t_item *item)
{
	t_list *ptr;
	t_item *item_ptr;

	ptr = state->items[item->production->index];
//	ft_printf("%d\n", ft_lstlen(state->items));
	while (ptr != NULL)
	{
		item_ptr = (t_item *)ptr->content;
		if(item_ptr->lookahead == item->lookahead &&
				item->progress->next == item_ptr->progress)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

/*
** returns the state eligible for the transition of 'item'
*/

t_state *sh_get_state_by_symbol(t_item *item, t_lr_parser *parser)
{
	t_list *ptr;
	t_state *state;

	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		if (sh_is_eligible_for_transition(state, item))
			return (state);
		ptr = ptr->next;
	}
	return (NULL);
}

/*
** returns the state linked to 'state' by the transition monitored by 'symbol'
*/

t_state	*sh_get_state_by_transition(t_state *state, t_symbol *symbol)
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

int		sh_add_transition(t_state *from, t_state *to, t_symbol *symbol)
{
	t_transition *transition;

	if (!(transition = sh_new_transition(to, symbol)))
		return (1);
	if (ft_lstaddnew_ptr_last(&from->transitions,
			transition, sizeof(t_transition)))
	{
		free(transition);
		return (1);
	}
	return (0);
}

t_item	*sh_new_item_advance(t_item *item)
{
	t_item *res;

	if (!(res = (t_item *)malloc(sizeof(t_item))))
		return (NULL);
	res->production = item->production;
	res->progress = item->progress->next;
	res->lookahead = item->lookahead;
	res->parsed = 0;
	return (res);
}

t_state *sh_new_parser_state_from_item(t_item *item, t_lr_parser *parser)
{
	t_state *res;
	t_item	*new_item;

	if (!(res = sh_new_state()))
		return (NULL);
	if (!(new_item = sh_new_item_advance(item)))
	{
		free(res);
		return (NULL);
	}
	if (ft_lstaddnew_ptr_last(&res->items[item->production->index], new_item,
			sizeof(t_item *)))
	{
		free(res);
		return (NULL);
	}
	if (ft_lstaddnew_ptr_last(&parser->states, res, sizeof(t_state *)))
	{
		sh_free_state(res);
		return (NULL);
	}
	return (res);
}

int		sh_is_in_state_progress_item(t_state *state, t_item *item)
{
	t_list *ptr;
	t_item *item_ptr;

	ptr = state->items[item->production->index];
	while (ptr != NULL)
	{
		item_ptr = (t_item *)ptr->content;
		if (item_ptr->lookahead == item->lookahead
			&& item->progress->next == item_ptr->progress)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

/*
** if the progressed item is not in state, adds it
*/

int		sh_add_to_state_check(t_state *state, t_item *item)
{
	t_item *new_item;

	if (sh_is_in_state_progress_item(state, item))
		return (0);
	else
	{
		if (!(new_item = sh_new_item_advance(item)))
			return (1);
		if (ft_lstaddnew_ptr_last(&state->items[new_item->production->index],
				new_item, sizeof(t_item *)))
		{
			free(new_item);
			return (1);
		}
		return (0);
	}
}

/*
** gets the state where the transition leads to for this item and creates the
** transition or both the state and the transition if necessary
** then add the convenient item as necessary in the given state
**
**		if there is already a transition in that state for that symbol
**
*/

int		sh_add_transition_item(t_item *item,
			t_state *state, t_lr_parser *parser, int *changes)
{
	t_state *res;

	if ((res = sh_get_state_by_transition(state,
			(t_symbol *)item->progress->content)))
	{
		if (sh_add_to_state_check(res, item))
		{
		//	if (res == state)
				*changes = 1;
			return (1);
		}
		return (0);
	}
	else
	{
		if (!(res = sh_get_state_by_symbol(item, parser)))
		{
			if (!(res = sh_new_parser_state_from_item(item, parser))) //ajouter dans tout les cas done
				return (1);
		//	if (res == state)
				*changes = 1;
		}
		if (sh_add_transition(state, res, item->progress->content))
			return (1);
		return (0);
	}
}

int		sh_process_compute_transitions(t_state *state, t_lr_parser *parser)
{
	t_list		*ptr;
	t_item		*item;
	int			i;
	int			changes;

	changes = 0;
	i = 0;
	while (i < NB_PRODUCTIONS)
	{
		ptr = state->items[i];
		while (ptr != NULL)
		{
			item = (t_item *)ptr->content;
			if (item->progress && sh_add_transition_item(item, state, parser, &changes))
				return (-1);
			ptr = ptr->next;
		}
		i++;
	}
	return (changes);
}

/*
** add all transitions for a state, creating other states if necessary
*/

int		sh_compute_transitions(t_state *state, t_lr_parser *parser)
{
	int ret;

	while ((ret = sh_process_compute_transitions(state, parser) == 1))
		;
	if (ret == -1)
		return (-1);
	return (0);
}
