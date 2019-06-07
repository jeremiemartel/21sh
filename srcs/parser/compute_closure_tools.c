/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_closure_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:28:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:34:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_add_to_closure(t_state *state,
			t_symbol *new_item, char first_sets[NB_TERMS])
{
	t_list			*ptr;
	t_production	*production;
	int				changes;
	t_item			*item;

	changes = 0;
	ptr = new_item->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (!(item = sh_get_state_item(production, state)))
		{
			if (sh_process_add_to_closure(production, state, first_sets))
				return (-1);
			changes = 1;
		}
		else
		{
			if (sh_update_lookaheads(item, first_sets))
				changes = 1;
		}
		ptr = ptr->next;
	}
	return (changes);
}

void		sh_compute_first_sets_str_append(char first_sets[NB_TERMS],
		t_list *w, t_symbol *append)
{
	t_list		*ptr;
	int			i;
	t_symbol	*symbol;
	int			eps_index;

	eps_index = sh_index(EPS);
	i = 0;
	while (i < NB_TERMS)
		first_sets[i++] = 0;
	ptr = w;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)ptr->content;
		sh_process_transitive_first_sets_2(first_sets, symbol);
		if (!symbol->first_sets[eps_index])
			return ;
		ptr = ptr->next;
	}
	sh_process_transitive_first_sets_2(first_sets, append);
	if (!append->first_sets[eps_index])
		return ;
	sh_process_transitive_first_set_2(first_sets, eps_index);
}
