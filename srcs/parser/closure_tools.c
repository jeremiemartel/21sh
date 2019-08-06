/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closure_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:58:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 05:10:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_item		*sh_get_state_item(t_production *production,
				t_state *state)
{
	t_list	*ptr;
	t_item	*item;

	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (item->production == production
			&& item->progress == item->production->symbols)
			return (item);
		ptr = ptr->next;
	}
	return (NULL);
}

t_item		*sh_new_item(t_production *production, char lookaheads[NB_TERMS])
{
	t_item	*res;
	int		i;

	if (!(res = malloc(sizeof(t_item))))
		return (NULL);
	res->production = production;
	res->progress = production->symbols;
	res->parsed = 0;
	i = 0;
	while (i < NB_TERMS)
	{
		res->lookaheads[i] = lookaheads[i];
		i++;
	}
	return (res);
}

int			sh_process_add_to_closure(t_production *production,
				t_state *state, char lookaheads[NB_TERMS])
{
	t_item *item;

	if (!(item = sh_new_item(production, lookaheads)))
		return (-1);
	if (ft_lstaddnew_ptr_last(&state->items, item, sizeof(t_item *)))
	{
		free(item);
		return (-1);
	}
	return (0);
}

t_symbol	*sh_get_next_non_terminal(t_item *item, t_list **w_ptr)
{
	t_symbol *res;

	if (item->progress == NULL)
		return (NULL);
	else
	{
		res = (t_symbol *)item->progress->content;
		*w_ptr = item->progress->next;
		return (res);
	}
}

int			sh_update_lookaheads(t_item *item, char lookaheads[NB_TERMS])
{
	int i;
	int changes;

	i = 0;
	changes = 0;
	while (i < NB_TERMS)
	{
		if (lookaheads[i] && !item->lookaheads[i])
		{
			item->lookaheads[i] = 1;
			changes = 1;
		}
		i++;
	}
	return (changes);
}
