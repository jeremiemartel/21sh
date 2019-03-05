/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldedier.parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/05 19:28:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(int id)
{
	return (id >= 0 && id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_test_token_id id,
		int val, t_token_type type)
{
	token->token_union.ival = val;
	token->token_id = id;
	token->token_type = type;
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
	ft_printf("\n");
}

int		sh_add_to_prod(t_symbol cfg_symbols[NB_SYMBOLS],
		t_list **symbols, int nb_symbols, ...)
{
	int		i;
	va_list	ap;
	int		symbol_index;

	*symbols = NULL;
	va_start(ap, nb_symbols);
	i = 0;
	while (i < nb_symbols)
	{
		symbol_index = va_arg(ap, int);
		if (ft_lstaddnew_ptr_last(symbols, &cfg_symbols[symbol_index],
					sizeof(t_symbol *)))
			return (1);
		i++;
	}
	va_end(ap);
	return (0);
}

int		ft_add_prod(t_symbol *symbol, t_list *prod_symbols)
{
	t_production *res;

	if (!(res = (t_production *)malloc(sizeof(t_symbol))))
		return (1);
	res->symbols = prod_symbols;
	if (ft_lstaddnew_ptr_last(&symbol->productions, res, sizeof(*res)))
	{
		free(res);
		return (1);
	}
	return (0);
}

//		(1) E → int
//		(2) E → (E Op E)

void	print_symbol(t_symbol *symbol)
{
	if (sh_is_term(symbol->id))
		ft_printf("%s%s%s", BLUE, symbol->debug, EOC);
	else
		ft_printf("%s%s%s", RED, symbol->debug, EOC);
}

int		init_E(t_cfg *cfg, t_symbol *symbol)
{
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols, &prod_symbols, 1,
			INT); //(1)
	ft_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols, &prod_symbols, 5,
			OPN_PARENT, E, OP, E, CLS_PARENT); //(2)
	ft_add_prod(symbol, prod_symbols);
	return (0);
}

//		(3) Op → +
//		(4) Op → *

int		init_Op(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols, &prod_symbols, 1,
			PLUS); //(1)
	ft_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols, &prod_symbols, 1, MULT); //(2)
	ft_add_prod(symbol, prod_symbols);
	return (0);
}

//		None

int		init_End_of_line(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	return (0);
}

/*
 ** attributes for each non_terminal every single of its productions
 */

static	int (*g_init_grammar_productions[NB_NOTERMS])
	(t_cfg *, t_symbol *symbol) = 
{
	init_E,
	init_Op,
	init_End_of_line
};

char		*get_debug(int index)
{
	static char *debug_str_tab[NB_SYMBOLS] = {
		"(",
		")",
		"+",
		"*",
		"INT",
		"ε",
		"E",
		"OP",
		"$"
	};
	return (debug_str_tab[index]);
}


void	init_symbol(t_symbol *symbol, t_test_token_id id)
{
	symbol->productions = NULL;
	symbol->first_sets = NULL;
	symbol->id = id;

	ft_strcpy(symbol->debug, get_debug(id));
}

void	print_production(t_production *production)
{
	t_list		*ptr;
	t_symbol	*symbol;
	int			start;

	start = 1;
	ptr = production->symbols;
	ft_printf("	");
	while (ptr != NULL)
	{
		symbol = (t_symbol *)(ptr->content);
		if (!start)
			ft_printf(" ");
		print_symbol(symbol);
		ptr = ptr->next;
		start = 0;
	}
	ft_printf("\n");
}

void	print_non_terminal_production(t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		print_production(production);
		ptr = ptr->next;
	}
}

void	print_non_terminals_productions(t_cfg *cfg)
{
	int i;
	int j;

	i = NB_TERMS;
	j = 0;
	while (j < NB_NOTERMS)
	{
		print_symbol(&(cfg->symbols[i]));
		ft_printf(" → \n");
	//	ft_printf("Non terminal [%s] Productions:\n", cfg->symbols[i].debug);
		print_non_terminal_production(&cfg->symbols[i++]);
		j++;
	}
}

int		init_context_free_grammar(t_cfg *cfg)
{
	int i;
	int j;

	ft_printf("%d\n", NB_TERMS);
	ft_printf("%d\n", NB_NOTERMS);
	cfg->start_index = E;
	i = 0;
	while (i < NB_SYMBOLS)
	{
		init_symbol(&cfg->symbols[i], i);
		i++;
	}
	i = NB_TERMS;
	j = 0;
	while (j < NB_NOTERMS)
	{
		if (g_init_grammar_productions[j++](cfg, &cfg->symbols[i++]))
			return (1);
	}
	return (0);
}

int		sh_parse_token_list(t_list *tokens)
{
	t_cfg	cfg;

	sh_print_token_list(tokens);
	if (init_context_free_grammar(&cfg))
		return (1);
	print_non_terminals_productions(&cfg);
	return (0);
}
