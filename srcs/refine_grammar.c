/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 06:11:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/22 05:54:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_refine_grammar_symbol(t_cfg *cfg, t_symbol *symbol, int symbol_index)
{
	(void)cfg;
	(void)symbol_index;
	t_list *ptr;
	t_list *ptr2;
	t_production *production;
	t_production *production2;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		ptr2 = ptr->next;
		while (ptr2 != NULL)
		{
			production2 = (t_production *)ptr2->content;

			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (0);
}

void	sh_remove_prod(t_symbol *symbol, t_production *production)
{
	t_list	*ptr;
	t_list	*prev;
	t_list	*tmp;

	ptr = symbol->productions;
	prev = NULL;
	while (ptr != NULL)
	{
		if (ptr->content == production)
		{
			tmp = ptr->next;
			ft_lstdel_ptr(&production->symbols);
			free(ptr);
			if (prev == NULL)
				symbol->productions = tmp;
			else
				prev->next = tmp;
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

int		sh_process_prod_first_follow_consume_list(t_symbol *symbol,
			t_list **list, t_symbol *ref)
{
	t_production	*prod;
	t_list			*ptr;
	t_symbol		*symbol_iter;

	prod = (t_production *)(*list)->content;
	ptr = prod->symbols;
	while (ptr != NULL)
	{
		symbol_iter = (t_symbol *)ptr->content;
		if (symbol_iter == ref)
		{

		}
		ptr = ptr->next;
	}
	*list = (*list)->next;
	(void)symbol;
	return (0);
}

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

int		sh_process_null_prod_first_follow_conflict(t_cfg *cfg, t_symbol *symbol)
{
	t_symbol		*symbol_iter;
	int				i;
	t_list			*ptr;
	t_list			*prev;
	t_list			*to_redispatch_prods;
	t_list			*tmp;

	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		to_redispatch_prods = NULL;
		symbol_iter = (t_symbol *)(cfg->symbols.tbl[i]);
		//if (symbol_iter != symbol)
		ptr = symbol_iter->productions;
		prev = NULL;
		while (ptr != NULL)
		{
			if (sh_has_symbol((t_production *)ptr->content, symbol))
			{
				tmp = ptr->next;
				if (prev == NULL)
				{
					ptr->next = NULL;
					ft_lstadd(&to_redispatch_prods, ptr);
					symbol_iter->productions = tmp;
				}
				else
				{
					ptr->next = NULL;
					ft_lstadd(&to_redispatch_prods, ptr);
					prev->next = tmp;
				}
			}
	//		sh_process_prod_first_follow_add_to_list(ptr->content,
	//			&to_redispatch_prods, symbol);
			prev = ptr;
			ptr = ptr->next;
		}
		while (to_redispatch_prods)
		{
			if (sh_process_prod_first_follow_consume_list(symbol_iter,
				&to_redispatch_prods, symbol))
				return (1);
		}
		i++;
	}
	return (0);
}

int		sh_refine_grammar_symbol_eps(t_cfg *cfg)
{
	t_symbol		*symbol;
	int				i;
	t_production	*production;

	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		symbol = (t_symbol *)(cfg->symbols.tbl[i]);
		if ((production = sh_get_null_production(symbol)) &&
			sh_intersect_sets(symbol->first_sets, symbol->follow_sets))
		{
			sh_remove_prod(symbol, production);
			if (sh_process_null_prod_first_follow_conflict(cfg, symbol))
				return (-1);
			ft_printf("OLALALAL\n");
			sh_print_symbol(symbol);
			ft_printf("\n");
		}
		i++;
	}
	return (0);
}

int		sh_process_refine_grammar(t_cfg *cfg)
{
	int changes;
	int ret;

	changes = 0;
	if ((ret = sh_refine_grammar_symbol_eps(cfg)) == -1)
		return (-1);
	changes |= ret;
//	changes |= sh_refine_grammar_symbol_eps();
	return (changes);
}

int     sh_refine_grammar(t_cfg *cfg)
{
	if (sh_compute_first_sets(cfg))
		return (-1);
	if (sh_compute_follow_sets(cfg))
		return (-1);
	return (sh_process_refine_grammar(cfg));
}
