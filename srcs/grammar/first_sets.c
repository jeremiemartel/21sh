/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:46:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:46:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_to_first_sets_by_prod(t_symbol *symbol,
			t_production *production, int *changes)
{
	t_list		*ptr;
	t_symbol	*prod_symbol;

	ptr = production->symbols;
	while (ptr != NULL)
	{
		prod_symbol = (t_symbol *)(ptr->content);
		sh_process_transitive_first_sets(symbol, prod_symbol, changes);
		if (!prod_symbol->first_sets[sh_index(EPS)])
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

int		sh_add_to_first_sets(t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;
	int				changes;

	changes = 0;
	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)(ptr->content);
		if (sh_add_to_first_sets_by_prod(symbol, production, &changes))
			sh_process_transitive_first_set(symbol, sh_index(EPS), &changes);
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_process_first_sets(t_cfg *cfg)
{
	int i;
	int j;
	int changes;

	i = NB_TERMS;
	j = 0;
	changes = 0;
	while (j < NB_NOTERMS)
	{
		if (sh_add_to_first_sets(&cfg->symbols[i]))
			changes = 1;
		j++;
		i++;
	}
	return (changes);
}

void	sh_init_process_first_sets(t_symbol *symbol)
{
	if (sh_is_term(symbol))
		symbol->first_sets[symbol->id] = 1;
	else if (has_eps_prod(symbol))
		symbol->first_sets[sh_index(EPS)] = 1;
}

int		sh_compute_first_sets(t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < NB_SYMBOLS)
	{
		sh_init_process_first_sets(&cfg->symbols[i]);
		i++;
	}
	while (sh_process_first_sets(cfg))
		;
	return (0);
}
