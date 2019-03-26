/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:51:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/26 15:19:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sh_21.h"

void	sh_process_populate_ll_table(t_cfg *cfg, int no_term_index,
			int term_index, t_production *production)
{
	t_production *old_prod;

	old_prod = cfg->ll_table[no_term_index][term_index];
	if (old_prod && old_prod != production)
	{
		ft_printf("ambiguous warning for symbol: ");
		sh_print_symbol(cfg->symbols.tbl[NB_TERMS + no_term_index]);
		ft_printf("\nwhen meeting token: ");
		sh_print_symbol(cfg->symbols.tbl[term_index]);
		ft_printf("\n");
		ft_printf("\nold production\n");
		sh_print_production(old_prod);
		ft_printf("\nnew production\n");
		sh_print_production(production);
		ft_printf("\n\n");
	}
	cfg->ll_table[no_term_index][term_index] = production;
}

void	populate_ll_table_by_sets(t_cfg *cfg, int no_term_index,
			char sets[NB_TERMS], t_production *production)
{
	int i;

	i = 0;
	while (i < NB_TERMS - 1) //not taking ε
	{
		if (sets[i])
			sh_process_populate_ll_table(cfg, no_term_index, i, production);
		i++;
	}
}

void	sh_add_symbol_prods(t_cfg *cfg, t_symbol *symbol, int no_term_index)
{
	t_list			*ptr;
	t_production	*production;
	char			first_sets[NB_TERMS];

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)(ptr->content);
		sh_compute_first_sets_str(cfg, first_sets, production->symbols);
		populate_ll_table_by_sets(cfg, no_term_index, first_sets, production);
		if (first_sets[EPS])
		{
			populate_ll_table_by_sets(cfg, no_term_index,
				symbol->follow_sets, production);
		}
		ptr = ptr->next;
	}
}

void	sh_process_ll_table(t_cfg *cfg)
{
	int i;
	int j;

	j = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		sh_add_symbol_prods(cfg, cfg->symbols.tbl[i++], j);
		j++;
	}
}

int		sh_compute_ll_table(t_cfg *cfg)
{
	int i;
	int j;

	i = 0;
	if (!(cfg->ll_table = (t_production ***)malloc((int)(cfg->symbols.current_size - NB_TERMS) * (int)(sizeof(t_production **)))))
		return (1);
	while (i < (int)cfg->symbols.current_size - (int)NB_TERMS)
	{
		if (!(cfg->ll_table[i] = (t_production **)malloc((int)(NB_TERMS) * (int)(sizeof(t_production *)))))
			return (1);
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
