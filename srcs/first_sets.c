/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:46:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/04 14:59:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_process_transitive_first_set(t_symbol *symbol,
			int index, int *changes)
{
	if (symbol->first_sets[index] == 0)
	{
		symbol->first_sets[index] = 1;
		*changes = 1;
	}
}

void	sh_process_transitive_first_sets(t_symbol *symbol,
			t_symbol *prod_symbol, int *changes)
{
	int i;

	i = 0;
	while (i < NB_TERMS - 1) // don't make ε belong to first if start with ε cause
		//						it might have others stuff behind
	{
		if (prod_symbol->first_sets[i] == 1)
			sh_process_transitive_first_set(symbol, i, changes);
		i++;
	}
}

void	sh_process_transitive_first_set_2(char first_sets[NB_TERMS], int index)
{
	if (first_sets[index] == 0)
		first_sets[index] = 1;
}

void	sh_process_transitive_first_sets_2(char first_sets[NB_TERMS],
			t_symbol *prod_symbol)
{
	int i;

	i = 0;
	while (i < NB_TERMS - 1) 	// don't make ε belong to first if start with ε cause
								// it might have others stuff behind
	{
		if (prod_symbol->first_sets[i] == 1)
			sh_process_transitive_first_set_2(first_sets, i);
		i++;
	}
}

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
		if (!prod_symbol->first_sets[EPS])
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
		production = (t_production *)(ptr->content); //itere sur chaque prod
		if (sh_add_to_first_sets_by_prod(symbol, production, &changes))
			sh_process_transitive_first_set(symbol, EPS, &changes);
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

int		is_eps_prod(t_production *production)
{
	t_list *symbols;
	t_symbol *symbol;

	symbols = production->symbols;
	symbol = symbols->content;
	if (ft_lstlen(symbols) == 1 && symbol->id == EPS)
		return (1);
	else
		return (0);
}

int		has_eps_prod(t_symbol *symbol)
{
	t_list *ptr;
	t_production *production;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (is_eps_prod(production))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	sh_init_process_first_sets(t_symbol *symbol)
{
	if (sh_is_term(symbol))
		symbol->first_sets[symbol->id] = 1;
	else if (has_eps_prod(symbol))
		symbol->first_sets[EPS] = 1;
}

/*
** populate first sets of list of symbols w
*/

int		sh_compute_first_sets_str(t_cfg *cfg,
			char first_sets[NB_TERMS], t_list *w)
{
	t_list		*ptr;
	t_symbol	*symbol;
	int			i;

	(void)cfg;
	i = 0;
	while (i < NB_TERMS)
		first_sets[i++] = 0;
	ptr = w;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)ptr->content;
//		sh_print_symbol(symbol);
//		ft_printf("\n");
//		sh_process_print_set(cfg, symbol->first_sets);
//		ft_printf("olalala\n");
		sh_process_transitive_first_sets_2(first_sets, symbol);
		if (!symbol->first_sets[EPS])
		{
//		sh_process_print_set(cfg, symbol->first_sets);
//		ft_printf("olalala\n");
			return (0);
		}
		ptr = ptr->next;
	}
	sh_process_transitive_first_set_2(first_sets, EPS);
	return (0);
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
