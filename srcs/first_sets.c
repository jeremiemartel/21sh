/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:46:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 18:59:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_process_transitive_first_sets(t_symbol *symbol,
			t_symbol *prod_symbol, int *changes)
{
	int i;

	i = 0;
	while (i < NB_TERMS)
	{
		if (prod_symbol->first_sets[i] == 1 && symbol->first_sets[i] == 0)
		{
			symbol->first_sets[i] = 1;
			*changes = 1;
		}
		i++;
	}
}

int		sh_add_to_first_sets(t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;
	t_symbol		*prod_symbol;
	int				changes;

	changes = 0;
	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)(ptr->content);
		if (production->symbols)
		{
			prod_symbol = (t_symbol *)(production->symbols->content);
			if (!sh_is_term(prod_symbol->id))
				sh_process_transitive_first_sets(symbol, prod_symbol, &changes);
		}
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
	t_list			*ptr;
	t_production	*production;
	t_symbol		*prod_symbol;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)(ptr->content);
		if (production->symbols)
		{
			prod_symbol = (t_symbol *)(production->symbols->content);
			if (sh_is_term(prod_symbol->id))
				symbol->first_sets[prod_symbol->id] = 1;
		}
		ptr = ptr->next;
	}
}

int		sh_init_first_sets(t_cfg *cfg)
{
	int i;
	int j;

	i = NB_TERMS;
	j = 0;
	while (j < NB_NOTERMS)
	{
		sh_init_process_first_sets(&cfg->symbols[i++]);
		j++;
	}
	while (sh_process_first_sets(cfg))
		;
	return (0);
}
