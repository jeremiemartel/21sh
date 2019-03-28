/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:46:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 18:10:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_eps_production(t_production *production)
{
	t_list *ptr;
	t_symbol *symbol;

	ptr = production->symbols;
	if (ft_lstlen(ptr) == 1)
	{
		symbol = (t_symbol *)ptr->content;
		return (symbol->id == EPS);
	}
	return (0);
}

t_production	*sh_get_null_production(t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (sh_is_eps_production(production))
			return (production);
		ptr = ptr->next;
	}
	return (NULL);
}

int		sh_nullable(t_symbol *symbol)
{
	return (symbol->first_sets[EPS]);
}

int		sh_intersect_sets(char set1[NB_TERMS], char set2[NB_TERMS])
{
	int i;

	i = 0;
	while (i < NB_TERMS)
	{
		if (set1[i] && set2[i])
			return (1);
		i++;
	}
	return (0);
}

void    sh_process_fill_set_index(char set[NB_TERMS],
		int index, int *changes)
{
	if (set[index] == 0)
	{
		set[index] = 1;
		*changes = 1;
	}
}

void    sh_process_fill_sets(char from[NB_TERMS],
		char to[NB_TERMS], int no_eps, int *changes)
{
	int i;

	i = 0;
	while (i < NB_TERMS - no_eps)
	{
		if (from[i] == 1)
			sh_process_fill_set_index(to, i, changes);
		i++;
	}
}

/*
 **	(1)	a)	A => aBb	=> First(b) in Follow(B) except for ε
 ** 		
 **	(2)	a)	A => aB 	=> 							=>	Follow(A) in Follow(B)
 **		b)	A => aBb	(where ε is in First(b))	=>	Follow(A) in Follow(B)
 **
 **					##	prod_symbol =	A ##
 **					##	ref 		=	B ##
 */

int		sh_process_follow_sets_symbol_ref_prod(t_cfg *cfg, t_symbol *prod_symbol,
		t_symbol *ref, t_production *production)
{
	t_list		*ptr;
	t_symbol	*symbol;
	char		first_sets[NB_TERMS];
	int			changes;

	changes = 0;
	ptr = production->symbols;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)ptr->content;
		if (symbol == ref)
		{
			if (ptr->next != NULL) //(1) a) aBb with b = ptr->next
			{
				/*
				   ft_printf("B: ");
				   sh_print_symbol(ref);
				   ft_printf("\n");
				   ft_printf("b: ");
				   sh_print_symbol_list(ptr->next);
				   ft_printf("\n\n");
				   ft_printf("\nfirst_sets de ");
				   sh_print_symbol_list(ptr->next);
				   ft_printf(":\n");
				 */
				sh_compute_first_sets_str(cfg, first_sets, ptr->next);

				/*sh_process_print_set(cfg, first_sets);
				  ft_printf("\nfollow_sets de ");
				  sh_print_symbol(ref);
				  ft_printf(":\n");
				 */
				sh_process_fill_sets(first_sets, ref->follow_sets, 1, &changes);
				/*
				   sh_process_print_set(cfg, ref->follow_sets);
				   ft_printf("\n");
				 */
				if (first_sets[EPS]) //(2) b)
				{
					sh_process_fill_sets(prod_symbol->follow_sets,
							ref->follow_sets, 0, &changes);
				}
			}
			else // (2) a)
			{
				//		ft_printf("ouai\n");
				sh_process_fill_sets(prod_symbol->follow_sets,
						ref->follow_sets, 0, &changes);
			}
		}
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_process_follow_sets_symbol_ref(t_cfg *cfg, t_symbol *prod_symbol, t_symbol *ref)
{
	t_list			*ptr;
	t_production	*production;
	int				changes;

	changes = 0;
	ptr = prod_symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (sh_process_follow_sets_symbol_ref_prod(cfg, prod_symbol, ref, production))
			changes = 1;
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_process_follow_sets_symbol(t_cfg *cfg, t_symbol *symbol)
{
	int			i;
	int			changes;
	t_symbol	*iter_symbol;

	changes = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		iter_symbol = (t_symbol *)cfg->symbols.tbl[i];
		if (iter_symbol->follow_sets[END_OF_INPUT] &&
			sh_process_follow_sets_symbol_ref(cfg, iter_symbol, symbol))
			changes = 1;
		i++;
	}
	return (changes);
}

int		sh_process_follow_sets(t_cfg *cfg)
{
	int changes;
	int i;

	changes = 0;
	i = NB_TERMS;
	while (i < (int)cfg->symbols.current_size)
	{
		if (sh_process_follow_sets_symbol(cfg, cfg->symbols.tbl[i]))
			changes = 1;
		i++;
	}
	return (changes);
}

int		sh_compute_follow_sets(t_cfg *cfg)
{
	int i;
	int j;

	i = 0;
	while (i < (int)cfg->symbols.current_size)
	{
		j = 0;
		while (j < NB_TERMS)
		{
			((t_symbol **)cfg->symbols.tbl)[i]->follow_sets[j] = 0;
			j++;
		}
		i++;
	}
	((t_symbol **)cfg->symbols.tbl)[cfg->start_index]->follow_sets[END_OF_INPUT] = 1;
	while (sh_process_follow_sets(cfg))
		;
	return (0);
}
