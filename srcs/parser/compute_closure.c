/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_closure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:34:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			process_process_compute_closure_item(t_state *state, t_item *item,
		char first_sets[NB_TERMS], t_lr_parser *parser)
{
	t_symbol	*next_non_terminal;
	t_list		*w_ptr;
	int			ret;

	if ((next_non_terminal = sh_get_next_non_terminal(item, &w_ptr)))
	{
		sh_compute_first_sets_str_append(first_sets,
				w_ptr, &parser->cfg.symbols[parser->index]);
		if ((ret = sh_add_to_closure(state,
						next_non_terminal, first_sets)))
		{
			if (ret == -1)
				return (-1);
			return (1);
		}
	}
	return (0);
}

/*
** If A → α · Bω [t] is in the state, add B → · γ [t]
** to the state for each production B → γ and for
** each terminal t ∈ FIRST*(ω t)
**
**
**		w_ptr				=>	ω
**		next_non_terminal	=>	B
**		item->lookahead		=>	t
*/

int			sh_process_compute_closure_item(t_item *item, t_state *state,
				t_lr_parser *parser)
{
	int			ret;
	int			changes;
	char		first_sets[NB_TERMS];
	int			i;

	changes = 0;
	i = 0;
	while (i < NB_TERMS)
	{
		if (item->lookaheads[i])
		{
			parser->index = i;
			if ((ret = process_process_compute_closure_item(state, item,
					first_sets, parser)) == -1)
				return (-1);
			else
				changes |= ret;
		}
		i++;
	}
	item->parsed = !changes;
	return (changes);
}

int			sh_process_compute_closure(t_state *state, t_lr_parser *parser)
{
	int		changes;
	t_list	*ptr;
	t_item	*item;
	int		ret;

	changes = 0;
	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (!item->parsed
			&& (ret = sh_process_compute_closure_item(item, state, parser)))
		{
			if (ret == -1)
				return (-1);
			changes = 1;
		}
		ptr = ptr->next;
	}
	return (changes);
}

int			sh_compute_closure(t_state *state, t_lr_parser *parser)
{
	int ret;
	int changes;

	changes = 0;
	while ((ret = sh_process_compute_closure(state, parser)) == 1)
		changes = 1;
	if (ret == -1)
		return (-1);
	return (changes);
}
