/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_closure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/04 18:19:57 by ldedier          ###   ########.fr       */
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
	int i;

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

int		sh_update_lookaheads(t_item *item, char lookaheads[NB_TERMS])
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

int		sh_add_to_closure(t_state *state,
			t_symbol *new_item, char first_sets[NB_TERMS], t_lr_parser *parser)
{
	t_list			*ptr;
	t_production	*production;
	int				changes;
	t_item			*item;
	(void)parser;
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

void	sh_compute_first_sets_str_append(char first_sets[NB_TERMS],
		t_list *w, t_symbol *append)
{
	t_list		*ptr;
	int			i;
	t_symbol	*symbol;

	i = 0;
	while (i < NB_TERMS)
		first_sets[i++] = 0;
	ptr = w;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)ptr->content;
		sh_process_transitive_first_sets_2(first_sets, symbol);
		if (!symbol->first_sets[EPS])
			return ;
		ptr = ptr->next;
	}
	sh_process_transitive_first_sets_2(first_sets, append);
	if (!append->first_sets[EPS])
		return ;
	sh_process_transitive_first_set_2(first_sets, EPS);
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

int		sh_process_compute_closure_item(t_item *item, t_state *state,
			t_lr_parser *parser)
{
	t_symbol	*next_non_terminal;
	t_list		*w_ptr;
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
			if ((next_non_terminal = sh_get_next_non_terminal(item, &w_ptr)))
			{
				sh_compute_first_sets_str_append(first_sets, w_ptr, &parser->cfg.symbols[i]);
				if ((ret = sh_add_to_closure(state, next_non_terminal, first_sets, parser)))
				{
					if (ret == -1)
						return (-1);
					changes = 1;
				}
			}
		}
		i++;
	}
	item->parsed = !changes;
	return (changes);
}

int		sh_process_compute_closure(t_state *state, t_lr_parser *parser)
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
		if (!item->parsed && (ret = sh_process_compute_closure_item(item, state, parser)))
		{
			if (ret == -1)
				return (-1);
			changes = 1;
		}
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_compute_closure(t_state *state, t_lr_parser *parser)
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
