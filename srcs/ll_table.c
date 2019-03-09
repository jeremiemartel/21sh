/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:51:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 22:25:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sh_21.h"

void	sh_process_populate_ll_table(t_cfg *cfg, int no_term_index,
			int term_index, t_production *production)
{
	t_production *old_prod;

	old_prod = cfg->ll_table[no_term_index][term_index];
	if (old_prod)
	{
		ft_printf("ambiguous warning !\n");
	}
	cfg->ll_table[no_term_index][term_index] = production;
}

void	populate_ll_table_by_first_sets(t_cfg *cfg,
			int no_term_index, t_symbol *no_term, t_production *production )
{
	int i;

	i = 0;
	while (i < NB_TERMS)
	{
		if (no_term->first_sets[i])
			sh_process_populate_ll_table(cfg, no_term_index, i, production);
		i++;
	}
}

void	sh_add_symbol_prods(t_cfg *cfg, t_symbol *symbol, int no_term_index)
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
			if (sh_is_term(prod_symbol))
				sh_process_populate_ll_table(cfg, no_term_index,
					prod_symbol->id, production);
			else
				populate_ll_table_by_first_sets(cfg, no_term_index,
						prod_symbol, production);
		}
		ptr = ptr->next;
	}
}

void	sh_process_ll_table(t_cfg *cfg)
{
	int i;
	int j;

	i = NB_TERMS;
	j = 0;
	while (j < NB_NOTERMS)
	{
		sh_add_symbol_prods(cfg, &cfg->symbols[i++], j);
		j++;
	}
}

int		sh_compute_ll_table(t_cfg *cfg)
{
	int i;
	int j;

	i = 0;
	while (i < NB_NOTERMS)
	{
		j = 0;
		while (j < NB_TERMS)
		{
			cfg->ll_table[i][j] = NULL;
			j++;
		}
		i++;
	}
	sh_process_ll_table(cfg);
	return (0);
}
