/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 06:11:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/26 18:53:06 by ldedier          ###   ########.fr       */
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

int		sh_process_add_eps_combinaisons(t_symbol *symbol, t_list_manager *lm,
		t_symbol *ref)
{
	t_symbol		*prod_symbol;
	t_production	*prod;
	t_list			*tmp;
	t_list			*tmp2;

	if (lm->current == NULL)
	{
		if (!(prod = sh_production_lst_dup_ptr(lm->head)))
			return (1);
		if (ft_lstaddnew_ptr_last(&symbol->productions, prod,
					sizeof(t_production)))
			return (1);
		return (0);
	}
	prod_symbol = (t_symbol *)lm->current->content;
	if (prod_symbol == ref)
	{
		if (lm->previous == NULL)
		{
			tmp = lm->head;
			tmp2 = lm->current;
			lm->head = lm->head->next;
			lm->current = lm->current->next;
			if (sh_process_add_eps_combinaisons(symbol, lm, ref))
				return (1);
			lm->head = tmp;
			lm->current = tmp2;
		}
		else
		{
			tmp = lm->current;
			tmp2 = lm->previous;

			lm->previous->next = lm->current->next;
			lm->current = lm->current->next;

			if (sh_process_add_eps_combinaisons(symbol, lm, ref))
				return (1);

			lm->current = tmp;
			lm->previous = tmp2;
			lm->previous->next = lm->current;
		}
	}
	lm->previous = lm->current;
	lm->current = lm->current->next;
	return (sh_process_add_eps_combinaisons(symbol, lm, ref));
}

int		sh_process_prod_first_follow_consume_list(t_symbol *symbol,
		t_list **list, t_symbol *ref)
{
	t_production	*prod;
	t_list_manager	lm;

	prod = (t_production *)(*list)->content;
	lm.head = prod->symbols;
	lm.current = prod->symbols;
	lm.previous = NULL;
	if (sh_process_add_eps_combinaisons(symbol, &lm, ref))
		return (1);
	*list = (*list)->next;
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
					ptr = symbol_iter->productions;
					continue;
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
	int				ret;

	ret = 0;
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
			ret = 1;
			ft_printf("eps refine: ");
			sh_print_symbol(symbol);
			ft_printf("\n");
		}
		i++;
	}
	return (ret);
}

void	link_lst(t_list **l1, t_list *l2)
{
	t_list *ptr;

	ptr = *l1;
	if (ptr == NULL)
		*l1 = l2;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = l2;
	}
}

int		sh_process_indirect_left_recursion(t_symbol *symbol,
		t_symbol *head_symbol, t_list *symbols)
{
	t_list			*ptr;
	int				ret;
	t_production	*production;
	t_list			*symbols_dup;

	ret = 0;
	ptr = head_symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;	
		if (!(symbols_dup = ft_lstdup_ptr(production->symbols)))
			return (-1);
		//		usleep(1000000);
		ft_printf("for symbol: ");
		sh_print_symbol(symbol);
		sh_print_symbol(head_symbol);
		ft_printf("\navant");
		sh_print_symbol_list(symbols_dup);
		link_lst(&symbols_dup, symbols);
		ft_printf("\napres");
		sh_print_symbol_list(symbols_dup);
		ft_printf("\n");
		//		usleep(1000000);
		ret |= sh_process_production_left_recursion(symbol, symbols_dup);
		ptr = ptr->next;
	}
	return (ret);
}

int		sh_process_production_left_recursion(t_symbol *symbol,
		t_list *symbols)
{
	int			ret;
	t_symbol	*head_symbol;

	ret = 0;
	if (!sh_is_term(head_symbol = (t_symbol *)symbols->content) &&
			head_symbol != symbol)
	{
		ret = 1;
		ft_lstpop_ptr(&symbols);
		sh_process_indirect_left_recursion(symbol, head_symbol, symbols);
	}
	else
	{
		if (head_symbol == symbol)
			ret = 1;
		ft_printf("on add:\n");
		sh_print_symbol_list(symbols);
		ft_printf("\n");
		sh_add_prod(symbol, symbols);
		//add prod from symbols to symbol
	}
	return (ret);
}

int		sh_direct_left_recursive(t_symbol *from, t_production *production)
{
	t_symbol *symbol;

	if (ft_lstlen(production->symbols) > 0)
	{
		symbol = (t_symbol *)production->symbols->content;
		return (symbol == from);
	}
	return (0);
}

int		sh_add_prod_new_symbol(t_cfg *cfg, t_symbol *new_symbol,
		t_production *production, t_symbol *from)
{
	t_symbol		*ptr;
	t_production	*prod;
	t_list			*symbols;

	(void)ptr;
	(void)from;
	if (!(prod = sh_production_lst_dup_ptr(production->symbols->next)))
		return (1);
	if (ft_lstaddnew_ptr_last(&prod->symbols,
				new_symbol, sizeof(t_symbol *)))
		return (1);
	if (ft_lstaddnew_ptr(&new_symbol->productions,
				prod, sizeof(t_production *)))
		return (1);
	if (!(prod = sh_production_lst_dup_ptr(production->symbols->next)))
		return (1);
	sh_add_to_prod(cfg->symbols.tbl, &symbols, 1, EPS);
	sh_add_prod(new_symbol, symbols);
	return (0);
}

int		sh_add_replace_prod_left_rec(t_symbol *symbol, t_symbol *new_symbol,
		t_production *production)
{
	t_production *prod;

	(void)new_symbol;
	if (!(prod = sh_production_lst_dup_ptr(production->symbols)))
		return (1);
	ft_printf("////////////////////////////////////////////////////\n");
	if (ft_lstaddnew_last(&prod->symbols, new_symbol, sizeof(t_symbol)))
		return (1);
	if (ft_lstaddnew_ptr_last(&symbol->productions, prod, sizeof(t_production)))
		return (1);
	return (0);
}

int		sh_direct_left_recursion_translate(t_cfg *cfg, t_symbol *symbol,
		t_production *production)
{
	t_production	*iter_prod;
	t_symbol		*new_symbol;
	t_list			*tmp;

	if (!(new_symbol = sh_new_symbol_from(symbol, cfg->symbols.current_size)))
		return (-1);
	if (sh_add_prod_new_symbol(cfg, new_symbol, production, symbol))
		return (-1);
	if (ft_dy_tab_add_ptr(&cfg->symbols, new_symbol))
	{
		free(new_symbol);
		return (-1);
	}
	tmp = symbol->productions;
	symbol->productions = NULL;
	while (tmp)
	{
		iter_prod = ft_lstpop_ptr(&tmp);
		if (iter_prod != production)
		{
			if (sh_add_replace_prod_left_rec(symbol, new_symbol, iter_prod))
				return (1);
		}
	}
	return (0);
}

int		sh_process_symbol_direct_left_recursion(t_cfg *cfg, t_symbol *symbol)
{
	t_list			*ptr;
	t_list			*prev;
	t_production	*production;
	t_list			*tmp;

	prev = NULL;
	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (sh_direct_left_recursive(symbol, production))
		{
			tmp = ptr;
			if (prev == NULL)
				symbol->productions = symbol->productions->next;
			else
				prev->next = ptr->next;
			ptr = ptr->next;
			sh_direct_left_recursion_translate(cfg, symbol, production);
			free(tmp);
			//	free(tmp->content);
			continue ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	sh_print_non_terminal_production(symbol);
	return (0);
}

int		sh_process_symbol_left_recursion(t_cfg *cfg, t_symbol *symbol)
{
	t_list			*ptr;
	t_list			*prev;
	t_production	*production;
	int				ret;
	int				ret2;
	t_list			*symbols_dup;
	t_list 			*tmp;

	ret2 = 0;
	prev = NULL;
	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (!sh_is_term((t_symbol *)production->symbols->content))
		{
			if (!(symbols_dup = ft_lstdup_ptr(production->symbols)))
				return (-1);
			sh_print_symbol(symbol);
			ft_printf("\n");
			sh_print_symbol_list(symbols_dup);
			ft_printf("\n");
			if ((ret = sh_process_production_left_recursion(symbol,
							symbols_dup)))
			{
				if (ret == -1)
					return (-1);
				ret2 = 1;
				tmp = ptr;
				if (prev == NULL)
					symbol->productions = symbol->productions->next;
				else
				{
					prev->next = ptr->next;
					//		prev = ptr;
				}
				ptr = ptr->next;
				free(tmp);
				//	free(tmp->content);
				sh_process_symbol_direct_left_recursion(cfg, symbol);
				return (1);
				//	continue;
			}
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (ret2);
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

int		sh_shows_first_to_first_conflicts(t_cfg *cfg,
			t_symbol *symbol, int *index)
{
	char			first_sets[NB_TERMS];
	char			prod_first_sets[NB_TERMS];
	int				i;
	t_list			*ptr;
	t_production	*production;

	i = 0;
	while (i < NB_TERMS)
		first_sets[i++] = 0;
	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		sh_compute_first_sets_str(cfg, prod_first_sets, production->symbols);
		if (sh_intersect_sets_2(first_sets, prod_first_sets, index))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int		sh_refine_grammar_left_recursion(t_cfg *cfg)
{
	t_symbol		*symbol;
	int				i;
	int				ret;
	int				ret2;
	int				dummy;

	ret2 = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		symbol = (t_symbol *)(cfg->symbols.tbl[i]);
		if (sh_shows_first_to_first_conflicts(cfg, symbol, &dummy))
		{
			if ((ret = sh_process_symbol_left_recursion(cfg, symbol)))
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

int		sh_add_prod_single_symbol(t_symbol *symbol, t_symbol *to_add_as_prod)
{
	t_list *prod_symbols;

	prod_symbols = NULL;
	if (ft_lstaddnew_ptr_last(&prod_symbols, to_add_as_prod, sizeof(t_symbol *)))
		return (1);
	if (sh_add_prod(symbol, prod_symbols))
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
	if (sh_add_prod(symbol, prod_symbols))
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

//	ft_printf(GREEN"FOR SYMBOL: "EOC);
//	sh_print_symbol(symbol);
//	ft_printf("\n");
//	sh_print_non_terminal_production(symbol);
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
** iterate over symbols, and split productions when factoring should be done
*/

int		sh_refine_grammar_factoring(t_cfg *cfg)
{
	t_symbol        *symbol;
	int             i;
	int             ret;
	int             ret2;
	int				index;

	ret2 = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		symbol = (t_symbol *)(cfg->symbols.tbl[i]);
		if (sh_shows_first_to_first_conflicts(cfg, symbol, &index))
		{
			if ((ret = sh_process_grammar_factoring(cfg,
					cfg->symbols.tbl[index], symbol)))
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
	int ret;

	changes = 0;
	if ((ret = sh_refine_grammar_symbol_eps(cfg)) == -1)
		return (-1);
	if (ret && sh_compute_sets(cfg))
		return (-1);
	changes |= ret;
	if ((ret = sh_refine_grammar_left_recursion(cfg)) == -1)
		return (-1);
	if (ret && sh_compute_sets(cfg))
		return (-1);
	changes |= ret;
	if (!changes)
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
	if (sh_compute_sets(cfg))
		return (1);
	return (sh_process_refine_grammar(cfg));
}
