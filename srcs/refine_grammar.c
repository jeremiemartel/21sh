/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 06:11:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 12:22:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_has_symbol(t_production *production, t_symbol *ref)
{
	t_list		*ptr;
	t_symbol	*symbol;

	ptr = production->symbols;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)ptr->content;
		if (symbol == ref)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int		sh_intersect_sets_2(char set1[NB_TERMS],
			char set2[NB_TERMS], int *index)
{
	int i;

	i = 0;
	while (i < NB_TERMS)
	{

		if (set2[i])
		{
			if (set1[i])
			{
				*index = i;
				return (1);
			}
			else
				set1[i] = 1;
		}
		i++;
	}
	return (0);
}

int		sh_add_prod_single_symbol(t_symbol *symbol, t_symbol *to_add_as_prod)
{
	t_list *prod_symbols;

	prod_symbols = NULL;
	if (ft_lstaddnew_ptr_last(&prod_symbols, to_add_as_prod, sizeof(t_symbol *)))
		return (1);
	if (sh_add_prod_from_symbols(symbol, prod_symbols))
		return (1);
	return (0);
}

int		sh_add_common_prod(t_symbol *symbol, t_symbol *factor, t_symbol *new)
{
	t_list *prod_symbols;

	prod_symbols = NULL;
	if (ft_lstaddnew_ptr_last(&prod_symbols, factor, sizeof(t_symbol *)))
		return (1);
	if (ft_lstaddnew_ptr_last(&prod_symbols, new, sizeof(t_symbol *)))
		return (1);
	if (sh_add_prod_from_symbols(symbol, prod_symbols))
		return (1);
	return (0);
}

/*
** split symbol into some new_symbol, based of the factor symbol
*/

int		sh_process_grammar_factoring(t_cfg *cfg,
			t_symbol *factor, t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;
	t_symbol		*new_symbol;
	t_list			*prev;
	t_list			*tmp;

	ft_printf(GREEN"FOR SYMBOL: "EOC);
	sh_print_symbol(symbol);
	ft_printf("\n");
	ft_printf(BLUE"FOR FACTOR: "EOC);
	sh_print_symbol(factor);
	ft_printf("\n");
	sh_print_non_terminal_production(symbol);
	if (!(new_symbol = sh_new_symbol_from(symbol, cfg->symbols.current_size)))
		return (1);
	if (ft_dy_tab_add_ptr(&cfg->symbols, new_symbol))
	{
		free(new_symbol);
		return (1);
	}
	ptr = symbol->productions;
	prev = NULL;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (production->symbols->content == factor) //pop then make new prod from it to new_symbol
		{
			tmp = ptr->next;
			if (prev == NULL)
				symbol->productions = symbol->productions->next;
			else
				prev->next = ptr->next;
			ft_lstpop_ptr(&production->symbols); //on supprime le facteur commun
			if (production->symbols)
			{
				ft_lstadd_last(&new_symbol->productions, ptr);
				ptr->next = NULL;
			}
			else
			{
			//	exit(1);
				if (sh_add_prod_single_symbol(new_symbol, cfg->symbols.tbl[EPS]))
					return (1);
				free(ptr);
			}
			ptr = tmp;
			continue ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (sh_add_common_prod(symbol, factor, new_symbol))
		return (1);
//	ft_printf("old symbol productions:\n");
//	sh_print_non_terminal_production(symbol);
//	ft_printf("new symbol productions:\n");
//	sh_print_non_terminal_production(new_symbol);
	return (0);
}

/*
** returns the first common symbol of every <symbol> productions
*/

t_symbol	*sh_get_common_factor(t_symbol *symbol)
{
	t_list			*ptr;
	t_list			*ptr2;
	t_production	*production;
	t_production	*production2;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		ptr2 = ptr->next;
		while (ptr2 != NULL)
		{
			production2 = (t_production *)ptr2->content;
			if (production->symbols->content == production2->symbols->content)
				return ((t_symbol *)production->symbols->content);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (NULL);
}

/*
** iterate over symbols, and split productions when factoring should be done
** sh_shows_first_to_first_conflicts(cfg, symbol, &index))
*/
int		sh_refine_grammar_factoring(t_cfg *cfg)
{
	t_symbol        *symbol;
	int             i;
	int             ret;
	int             ret2;
	t_symbol		*factor;

	ret2 = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		symbol = (t_symbol *)(cfg->symbols.tbl[i]);
		while ((factor = sh_get_common_factor(symbol)))
		{
			if ((ret = sh_process_grammar_factoring(cfg, factor, symbol)))
			{
				if (ret == -1)
					return (-1);
				ret2 = 1;
			}
		}
		i++;
	}
	return (ret2);
}

int		sh_compute_sets(t_cfg *cfg)
{
	if (sh_compute_first_sets(cfg))
		return (1);
	if (sh_compute_follow_sets(cfg))
		return (1);
	return (0);
}

int		sh_process_refine_grammar(t_cfg *cfg)
{
	int changes;
	int	ret;
	int	ref_left_recur = 1;
	int	ref_factor = 1;
	int	ref_eps = 1;


	changes = 0;
	if (ref_eps)
	{
		if ((ret = sh_refine_grammar_symbol_eps(cfg)) == -1)
			return (-1);
		if (ret && sh_compute_sets(cfg))
			return (-1);
		changes |= ret;
	}
	ret = 0;
	if (ref_left_recur)
	{
		if ((ret = sh_refine_grammar_left_recursion(cfg)) == -1)
			return (-1);
		if (ret && sh_compute_sets(cfg))
			return (-1);
		changes |= ret;
	}
	ret = 0;
	if (ref_factor)
	{
		if ((ret = sh_refine_grammar_factoring(cfg)) == -1)
			return (-1);
		if (ret && sh_compute_sets(cfg))
			return (-1);
		changes |= ret;
	}
	return (changes);
}

int		sh_refine_grammar(t_cfg *cfg)
{
	static int i = 0;

	ft_printf("passage refine: %d\n", ++i);
	sh_print_non_terminals_productions(cfg);
//	if (i == 2)
//		exit(1);
	if (sh_compute_sets(cfg))
		return (1);
	return (sh_process_refine_grammar(cfg));
}
