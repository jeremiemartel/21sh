/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:04:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/12 17:57:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void    sh_print_symbol(t_symbol *symbol)
{
	if (sh_is_term(symbol))
		ft_printf("%s%s%s", BLUE, symbol->debug, EOC);
	else
		ft_printf("%s%s%s", RED, symbol->debug, EOC);
}
/*
void	sh_print_token(t_token *token)
{
	if (token->token_type == TYPE_INT)
		ft_printf("%d", token->token_union.ival);
	else
	{
		if (token->token_id == PLUS)
			ft_printf("+");
		else if (token->token_id == MULT)
			ft_printf("*");
		else if (token->token_id == OPN_PARENT)
			ft_printf("(");
		else if (token->token_id == CLS_PARENT)
			ft_printf(")");
	}
}
void	sh_print_token_list(t_list *list)
{
	t_list *ptr;

	ptr = list;
	ft_printf("token list: ");
	while (ptr != NULL)
	{
		sh_print_token(ptr->content);
		ptr = ptr->next;
	}
	ft_printf("\n\n");
}
*/

void	sh_print_symbol_list(t_list *symbols)
{
	t_list		*ptr;
	int			start;
	t_symbol	*symbol;

	start = 1;
	ptr =  symbols;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)(ptr->content);
		if (!start)
			ft_printf(" ");
		sh_print_symbol(symbol);
		ptr = ptr->next;
		start = 0;
	}
}

void	sh_print_production(t_production *production)
{
	sh_print_symbol_list(production->symbols);
}


void	print_non_terminal_production(t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		ft_printf("\t");
		sh_print_production(production);
		ft_printf("\n");
		ptr = ptr->next;
	}
}

void	print_non_terminals_productions(t_cfg *cfg)
{
	int i;
	int j;

	i = NB_TERMS;
	j = 0;
	ft_printf(BOLD UNDERLINE"PRODUCTIONS:\n\n"EOC);
	while (j < NB_NOTERMS)
	{
		sh_print_symbol(((t_symbol **)(cfg->symbols.tbl))[i]);
		ft_printf(" → \n");
		print_non_terminal_production(((t_symbol **)(cfg->symbols.tbl))[i++]);
		j++;
	}
	ft_printf("\n");
}

void	sh_process_print_set(t_cfg *cfg, char sets[NB_TERMS])
{
	int i;
	int first;

	i = 0;
	first = 1;
	while (i < NB_TERMS)
	{
		if (sets[i])
		{
			if (!first)
				ft_printf(" ; ");
			sh_print_symbol(((t_symbol **)(cfg->symbols.tbl))[i]);
			first = 0;
		}
		i++;
	}
}

void	sh_print_first_set(t_cfg *cfg, t_symbol *symbol)
{
	ft_printf("first sets of ");
	sh_print_symbol(symbol);
	ft_printf(" :\n");
	sh_process_print_set(cfg, symbol->first_sets);
	ft_printf("\n\n");
}

void	sh_print_follow_set(t_cfg *cfg, t_symbol *symbol)
{
	ft_printf("follow sets of ");
	sh_print_symbol(symbol);
	ft_printf(" :\n");
	sh_process_print_set(cfg, symbol->follow_sets);
	ft_printf("\n\n");
}


void	print_follow_sets(t_cfg *cfg)
{
	int i;
	int j;

	i = NB_TERMS;
	j = 0;
	ft_printf(BOLD UNDERLINE"FOLLOW SETS:\n\n"EOC);
	while (j < NB_NOTERMS)
	{
		sh_print_follow_set(cfg, ((t_symbol **)(cfg->symbols.tbl))[i++]);
		j++;
	}
}

void	print_first_sets(t_cfg *cfg)
{
	int i;
	int j;

	i = NB_TERMS;
	j = 0;
	ft_printf(BOLD UNDERLINE"FIRST SETS:\n\n"EOC);
	while (j < NB_NOTERMS)
	{
		sh_print_first_set(cfg, ((t_symbol **)(cfg->symbols.tbl))[i++]);
		j++;
	}
}

int     ft_strlen_utf8(char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (!(str[i] & 0b10000000))
			i++;
		else if (str[i] & 0b01000000 && !(str[i] & 0b00100000))
			i += 2;
		else if (str[i] & 0b00100000 && !(str[i] & 0b00010000))
			i += 3;
		else if (str[i] & 0b000100000 && !(str[i] & 0b00001000))
			i += 4;
		else
			i++;
		res++;
	}
	return (res);
}

int		prod_debug_len(t_production *production)
{
	int			res;
	t_list		*ptr;
	t_symbol	*symbol;

	res = 0;
	ptr = production->symbols;
	while (ptr != NULL)
	{
		if (ptr != production->symbols)
			res++;
		symbol = (t_symbol *)(ptr->content);
		res += ft_strlen_utf8(symbol->debug);
		ptr = ptr->next;
	}
	return (res);
}

void	print_ll_table(t_cfg *cfg)
{
	int				i;
	int				j;
	t_production	*production;
	int				len;

	ft_printf(BOLD UNDERLINE"LL TABLE:\n\n"EOC);
	j = 0;
	ft_printf("\t\t");
	while (j < NB_TERMS)
	{
		ft_printf("%s%s%s\t\t",BLUE, ((t_symbol **)(cfg->symbols.tbl))[j]->debug, EOC);
		j++;
	}
	ft_printf("\n");
	i = 0;
	while (i < NB_NOTERMS)
	{
		j = 0;
		ft_printf("%s%s%s\t\t", RED, ((t_symbol **)(cfg->symbols.tbl))[NB_TERMS + i]->debug, EOC);
		while (j < NB_TERMS)
		{
			production = cfg->ll_table[i][j];
			if (production == NULL)
				ft_printf("NULL\t\t");
			else
			{
				len = prod_debug_len(production);
				//		ft_printf("%d\n", len);
				sh_print_production(production);
				while (len <= 16)
				{
					ft_printf("\t");
					len += 8;
				}
			}
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
void	sh_print_pda(t_list *guess)
{
	ft_printf("guess: ");
	sh_print_symbol_list(guess);
	ft_printf("\n");
}

void	print_cfg(t_cfg *cfg)
{
	print_non_terminals_productions(cfg);
	print_first_sets(cfg);
	print_follow_sets(cfg);
	print_ll_table(cfg);
}
