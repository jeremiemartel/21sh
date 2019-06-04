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
	if (ft_lstaddnew_ptr_last(&res->items, new_item, sizeof(t_item *)))
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

int		sh_add_to_state_check(t_state *state, t_item *item, int *changes)
{
	t_item *new_item;

	if (sh_is_eligible_for_transition(state, item))
		return (0);
	else
	{
		if (!(new_item = sh_new_item_advance(item)))
			return (1);
		if (ft_lstaddnew_ptr_last(&state->items, new_item, sizeof(t_item *)))
		{
			free(new_item);
			return (1);
		}
		*changes = 1;
		return (0);
	}
}

/*
** gets the state where the transition leads to for this item and creates the
** transition or both the state and the transition if necessary
** then add the convenient item as necessary in the given state
**
*/

int		sh_add_transition_item(t_item *item,
			t_state *state, t_lr_parser *parser, int *changes)
{
	t_state *res;

	if ((res = sh_get_state_by_transition(state,
			(t_symbol *)item->progress->content)))
	{
		if (sh_add_to_state_check(res, item, changes))
			return (1);
		return (0);
	}
	else
	{
		if (!(res = sh_get_state_by_symbol(item, parser)))
		{
			if (!(res = sh_new_parser_state_from_item(item, parser))) //ajouter dans tout les cas done
				return (1);
		}
		if (sh_add_transition(state, res, item->progress->content))
			return (1);
		*changes = 1;
		return (0);
	}
}

int		sh_compute_transitions(t_state *state, t_lr_parser *parser)
{
	t_list		*ptr;
	t_item		*item;
	int			changes;

	ptr = state->items;
	changes = 0;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (item->progress && sh_add_transition_item(item, state,
					parser, &changes))
			return (-1);
		ptr = ptr->next;
	}
	return (changes);
}
