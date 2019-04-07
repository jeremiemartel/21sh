/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 17:13:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
	t_production	*res;
	static int		index = 1;

	if (!(res = (t_production *)malloc(sizeof(t_symbol))))
		return (1);
	res->index = index++;
	res->from = symbol;
	res->symbols = prod_symbols;
	if (ft_lstaddnew_ptr_last(&symbol->productions, res, sizeof(*res)))
	{
		free(res);
		return (1);
	}
	return (0);
}

int		init_start_symbol(t_cfg *cfg, t_symbol *symbol)
{
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols, &prod_symbols, 1, E); //(1)
	ft_add_prod(symbol, prod_symbols);
	ft_strcpy(symbol->debug, "S");
	return (0);
}


//		(1) E → int
//		(2) E → (E Op E)

int		init_E(t_cfg *cfg, t_symbol *symbol)
{
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols, &prod_symbols, 3, E, PLUS, T); //(2)
	ft_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols, &prod_symbols, 1, T); //(1)
	ft_add_prod(symbol, prod_symbols);
	return (0);
}

//		(3) Op → +
//		(4) Op → *

int		init_T(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols, &prod_symbols, 3, T, MULT, F); //(2)
	ft_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols, &prod_symbols, 1,
		F); //(1)
	ft_add_prod(symbol, prod_symbols);
	return (0);
}

int		init_F(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols, &prod_symbols, 3, OPN_PARENT, E, CLS_PARENT); //(2)
	ft_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols, &prod_symbols, 1, INT); //(1)
	ft_add_prod(symbol, prod_symbols);
	return (0);
}


//		None

/*
 ** attributes for each non_terminal every single of its productions
 */

static	int (*g_init_grammar_productions[NB_NOTERMS])
	(t_cfg *, t_symbol *symbol) = 
{
	init_E,
	init_T,
	init_F
};

char		*get_debug(int index)
{
	static char *debug_str_tab[NB_SYMBOLS] = {
		"(",
		")",
		"+",
		"*",
		"int",
		"$",
		"ε",
		"E",
		"T",
		"F"
	};
	return (debug_str_tab[index]);
}

void	init_symbol(t_symbol *symbol, t_test_token_id id)
{
	int i;

	i = 0;
	while (i < NB_TERMS)
	{
		symbol->first_sets[i] = 0;
		symbol->follow_sets[i] = 0;
		i++;
	}
	symbol->productions = NULL;
	symbol->id = id;
	symbol->relevant = 1;
	symbol->replacing = 0;
	ft_strcpy(symbol->debug, get_debug(id));
}

int		init_context_free_grammar(t_cfg *cfg)
{
	int i;
	int j;

	i = 0;
	while (i < NB_SYMBOLS)
	{
		init_symbol(&cfg->symbols[i], i);
		i++;
	}
	init_symbol(&cfg->start_symbol, i);

	cfg->symbols[OPN_PARENT].relevant = 0;
	cfg->symbols[CLS_PARENT].relevant = 0;
	i = NB_TERMS;
	j = 0;
	while (j < NB_NOTERMS)
	{
		if (g_init_grammar_productions[j++](cfg, &cfg->symbols[i++]))
			return (1);
	}
	init_start_symbol(cfg, &cfg->start_symbol);
	if (sh_compute_first_sets(cfg))
		return (1);
	if (sh_compute_follow_sets(cfg))
		return (1);
	return (0);
}

int sh_parse_token_list(t_list *tokens)
{
	t_lr_parser	parser;

	parser.tokens = tokens;
	init_context_free_grammar(&parser.cfg);
//	print_cfg(&parser.cfg);
	if (sh_compute_lr_automata(&parser))
		return (1);
//	sh_print_automata(&parser, 1);
	sh_compute_lr_tables(&parser);
	sh_print_parser(&parser, 0);
	if (sh_lr_parse(&parser))
	{
		ft_printf("LEXICAL ERROR\n");
		return (1);
	}
	else
		ft_printf("OK !\n");
	return (0);
}
