/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 06:11:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/30 16:04:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** append l2 to l1
**
**		l1: a->b->c
** 		l2: d->e->f
**
** *call link_lst(&l1, l2);
**
** l1: a->b->c->d->e->f
**				l2
*/

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

/*
** iterate on head_symbol productions and return if one of the computed
** list of production->symbols linked to symbols shows left recursion
**
**			A -> B⍺
**			B -> Cɣ | ω
**			C -> AΦ : indirect left recursion with A
**
**			symbol 		=> A
**			head_symbol => B
**			symbols		=> ⍺
**
**		this create new symbol list C ɣ ⍺ and ω ⍺ (all concatenation of prods(B)
**		and rest of the given A production) to test its left recursion with A
*/

int		sh_process_indirect_left_recursion(t_symbol *symbol,
		t_symbol *head_symbol, t_list *symbols)
{
	t_list			*ptr;
	int				ret;
	t_production	*production;
	t_list			*symbols_dup;

//	ft_printf("symbol: ");
//	sh_print_symbol(symbol);
//	ft_printf("\n");
	ret = 0;
	ptr = head_symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;

		ft_printf("PRODUCTION: ");
		sh_print_production(production);
		ft_printf("\n");
		ft_printf("SYMBOLS: ");
		sh_print_symbol_list(symbols);
		ft_printf("\n");

		if (!(symbols_dup = ft_lstdup_ptr(production->symbols)))
			return (-1);
		if (sh_is_eps_production(production))
		{
			if (symbols)
				ret |= sh_process_production_left_recursion(symbol, ft_lstdup_ptr(symbols));
		}
		else
		{
			link_lst(&symbols_dup, symbols);
			ret |= sh_process_production_left_recursion(symbol, ft_lstdup_ptr(symbols_dup));
		}
//		ft_printf("for symbol: ");
//		sh_print_symbol(symbol);
//		ft_printf("\nfor head symbol: ");

//		sh_print_symbol(head_symbol);
//		ft_printf("\navant");
//		sh_print_symbol_list(symbols_dup);

	//	link_lst(&symbols_dup, symbols);

//		ft_printf("\napres");
//		sh_print_symbol_list(symbols_dup);
//		ft_printf("\n");

	//	ret |= sh_process_production_left_recursion(symbol, symbols_dup);
		ptr = ptr->next;
	}
	return (ret);
}

/*
** return 1 if symbols has a non terminal at the leftmost symbol of its RHS
*/

int		sh_process_production_left_recursion(t_symbol *symbol,
			t_list *symbols)
{
	int			ret;
	t_symbol	*head_symbol;

	ret = 0;
	ft_printf(GREEN"LALALALALALALALALAL"EOC);
	sh_print_symbol_list(symbols);
	sh_print_symbol_list(symbols);
	sh_print_symbol_list(symbols);
	ft_printf("OUAIAIA\n");
	ft_printf("\n");
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
		ft_printf("\n au symbol ");
		sh_print_symbol(symbol);
		sh_add_prod_from_symbols(symbol, symbols); //check if does not exist already
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

/*
**		when direct left recursion occurs:
**
**			A -> A⍺ | β gets transformed into:
**			
**					A -> βA'
**					A'-> ⍺A' | ε
**
**			this function takes care of this part
**
**					A'-> ⍺A' | ε
**
**			with
**				⍺ => production->symbols->next
**				A'=> new_symbol
*/

int		sh_add_prod_new_symbol(t_symbol *new_symbol,
		t_production *production)
{
	t_production	*prod;

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
	return (0);
}

int		sh_add_replace_prod_left_rec(t_symbol *symbol, t_symbol *new_symbol,
		t_production *production, t_list *ptr)
{
	t_production *prod;

	if (!(prod = sh_production_lst_dup_ptr(production->symbols)))
		return (1);
	if (ft_lstaddnew_ptr_last(&prod->symbols, new_symbol, sizeof(t_symbol)))
		return (1);
	//free(ptr->content);
	ptr->content = prod;
	(void)symbol;
	// if (ft_lstaddnew_ptr_last(&symbol->productions, prod, sizeof(t_production)))
		// return (1);
	return (0);
}

/*
** split production when direct left recursion occurs 
**			
**			A -> A⍺ | β gets transformed into:
**			
**					A -> βA'
**					A'-> ⍺A' | ε
**
**			with 
**				A  => symbol
**				A' => new_symbol
**				(A -> A⍺) => productions
*/

int		sh_direct_left_recursion_translate(t_cfg *cfg, t_symbol *symbol,
		t_production *production, t_symbol **new_symbol)
{
	t_production	*iter_prod;
	t_list			*ptr;

	if (!*new_symbol)
	{
		if (!(*new_symbol = sh_new_symbol_from(symbol, cfg->symbols.current_size)))
			return (-1);
		if (ft_dy_tab_add_ptr(&cfg->symbols, *new_symbol))
		{
			free(*new_symbol);
			return (-1);
		}
	}
	if (sh_add_prod_new_symbol(*new_symbol, production))
		return (-1);
	ptr = symbol->productions;
	while (ptr != NULL)
	{
		iter_prod = (t_production *)(ptr->content);
		// iif (iter_prod != production)
		// {
			if (sh_add_replace_prod_left_rec(symbol, *new_symbol, iter_prod, ptr))
				return (1);
		// }
		ptr = ptr->next;
	}
	return (0);
}

int		sh_process_symbol_direct_left_recursion(t_cfg *cfg, t_symbol *symbol)
{
	t_list			*ptr;
	t_list			*prev;
	t_production	*production;
	t_list			*tmp;
	t_symbol		*new_symbol;
	t_list			*symbols;

	new_symbol = NULL;
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
			sh_direct_left_recursion_translate(cfg, symbol, production, &new_symbol);
			free(tmp);
			//	free(tmp->content);
			continue ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (new_symbol)
	{
		symbols = NULL;
		if (ft_lstaddnew_ptr(&symbols, cfg->symbols.tbl[EPS], sizeof(t_symbol *)))
			return (1);
		sh_add_prod_from_symbols(new_symbol, symbols);
	}
//	sh_print_non_terminal_production(symbol);
	return (0);
}

/*
** iterate over production of symbol, if it has a non terminal as the first RHS symbol, delete the production
** replace
*/

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
	//		sh_print_symbol(symbol);
	//		ft_printf("\n");
	//		sh_print_symbol_list(symbols_dup);
	//		ft_printf("\n");

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

int		sh_refine_grammar_direct_left_recursion(t_cfg *cfg)
{
	int			i;
	t_symbol	*symbol;

	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		symbol = (t_symbol *)(cfg->symbols.tbl[i]);
		sh_process_symbol_direct_left_recursion(cfg, symbol); //to_protect
		i++;
	}
	return (0);	
}

/*
** remove left recursion in all the cfg 
*/

int		sh_refine_grammar_left_recursion(t_cfg *cfg)
{
	t_symbol		*symbol;
	int				i;
	int				ret;
	int				ret2;
	int				dummy;

(void)ret;
	sh_refine_grammar_direct_left_recursion(cfg);
	ret2 = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		symbol = (t_symbol *)(cfg->symbols.tbl[i]);
		if (sh_shows_first_to_first_conflicts(cfg, symbol, &dummy))
		{
	//		ft_printf("SYMBOL:::\n");
	//		sh_print_symbol(cfg->symbols.tbl[dummy]);
			if ((ret = sh_process_symbol_left_recursion(cfg, symbol)))
			{
				if (ret == -1)
					return (-1);
				ret2 = 1;
			}
		}
		i++;
	}
	if (ret2)
		sh_refine_grammar_left_recursion(cfg);
	return (ret2);
}
