/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/26 18:53:12 by ldedier          ###   ########.fr       */
/*      h                                                                     */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol)
{
	return (symbol->id >= 0 && symbol->id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_test_token_id id,
		int val, t_token_type type)
{
	token->token_union.ival = val;
	token->token_id = id;
	token->token_type = type;
}


int		sh_add_to_prod(void **vcfg_symbols,
		t_list **symbols, int nb_symbols, ...)
{
	int		i;
	va_list	ap;
	int		symbol_index;
	t_symbol **cfg_symbols;

	cfg_symbols = (t_symbol **)vcfg_symbols;
	*symbols = NULL;
	va_start(ap, nb_symbols);
	i = 0;
	while (i < nb_symbols)
	{
		symbol_index = va_arg(ap, int);
		if (ft_lstaddnew_ptr_last(symbols, cfg_symbols[symbol_index],
					sizeof(t_symbol *)))
			return (1);
		i++;
	}
	va_end(ap);
	return (0);
}

t_production	*sh_production_lst_dup_ptr(t_list *symbols)
{
	t_production *res;
	t_list *ptr;

	if (!(res = (t_production *)malloc(sizeof(t_symbol))))
		return (NULL);
	res->symbols = NULL;
	ptr = symbols;
	while (ptr != NULL)
	{
		if (ft_lstaddnew_ptr_last(&res->symbols, ptr->content, sizeof(t_symbol)))
		{
			//free
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (res);
}

int		sh_add_prod(t_symbol *symbol, t_list *prod_symbols)
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

int		init_S(t_cfg *cfg, t_symbol *symbol)
{
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 2, A, END_OF_INPUT);
	sh_add_prod(symbol, prod_symbols);
	return (0);
}

//		(3) Op → +
//		(4) Op → *

int		init_A(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 3,
			B, T_A, C); //(1)
	sh_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 3,
			B, T_A, T_D); //(1)
	sh_add_prod(symbol, prod_symbols);
	return (0);
}

int		init_B(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 1, T_A); //(1)
	sh_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 1, EPS);
	sh_add_prod(symbol, prod_symbols);
	return (0);
}

int		init_C(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 1, D);
	sh_add_prod(symbol, prod_symbols);
	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 1, T_B);
	sh_add_prod(symbol, prod_symbols);
	return (0);
}

int		init_D(t_cfg *cfg, t_symbol *symbol)
{
	(void)symbol;
	(void)cfg;
	t_list *prod_symbols;

	sh_add_to_prod(cfg->symbols.tbl, &prod_symbols, 2, C, T_C);
	sh_add_prod(symbol, prod_symbols);
	return (0);
}

//		None
/*
 ** attributes for each non_terminal every single of its productions
 */

static	int (*g_init_grammar_productions[NB_NOTERMS])
	(t_cfg *, t_symbol *symbol) = 
{
	init_S,
	init_A,
	init_B,
	init_C,
	init_D
};

char		*get_debug(int index)
{
	static char *debug_str_tab[NB_SYMBOLS] = {
		"a",
		"b",
		"c",
		"d",
		"$",
		"ε",
		"S",
		"A",
		"B",
		"C",
		"D",
	};
	return (debug_str_tab[index]);
}

t_symbol	*new_symbol(t_test_token_id id)
{
	t_symbol	*symbol;
	int			i;
	
	if (!(symbol = (t_symbol *)malloc(sizeof(t_symbol))))
		return (NULL);
	i = 0;
	while (i < NB_TERMS)
	{
		symbol->first_sets[i] = 0;
		symbol->follow_sets[i] = 0;
		i++;
	}
	symbol->productions = NULL;
	symbol->id = id;
	symbol->splits = 0;
	ft_strcpy(symbol->debug, get_debug(id));
	return (symbol);
}

t_symbol	*sh_new_symbol_from(t_symbol *from, t_test_token_id id)
{
	t_symbol	*symbol;
	int			i;
	char		*str;

	if (!(symbol = (t_symbol *)ft_memalloc(sizeof(t_symbol))))
		return (NULL);
	i = 0;
	while (i < NB_TERMS)
	{
		symbol->first_sets[i] = 0;
		symbol->follow_sets[i] = 0;
		i++;
	}
	symbol->productions = NULL;
	symbol->id = id;
	if (!(str = ft_itoa(++from->splits)))
		return (symbol);
	ft_strcpy(symbol->debug, from->debug);
	ft_strlcat(symbol->debug, "(", sizeof(symbol->debug));
	ft_strlcat(symbol->debug, str, sizeof(symbol->debug));
	ft_strlcat(symbol->debug, ")", sizeof(symbol->debug));
	free(str);
	return (symbol);
}

int		init_context_free_grammar(t_cfg *cfg)
{
	int			i;
	int			j;
	int			ret;
	t_symbol	*new;

	cfg->start_index = S;
	i = 0;
	if (ft_dy_tab_init(&cfg->symbols, 128))
		return (1);
	while (i < NB_SYMBOLS)
	{
		if (!((new = new_symbol(i))))
		{
			//free dy tab
			return (1);
		}
		if (ft_dy_tab_add_ptr(&cfg->symbols, new))
		{
			free(new);
			//free dy tab
			return (1);
		}
		i++;
	}
	i = NB_TERMS;
	j = 0;
	while (j < NB_NOTERMS)
	{
		if (g_init_grammar_productions[j++](cfg, ((t_symbol **)(cfg->symbols.tbl))[i++]))
			return (1);
	}
//	if (sh_compute_first_sets(cfg))
//		return (1);
//	if (sh_compute_follow_sets(cfg))
//		return (1);
	while ((ret = sh_refine_grammar(cfg)) == 1)
		;
	if (ret == -1)
		return (1);
	if (sh_compute_ll_table(cfg))
		return (1);
	return (0);
}

int		sh_process_test(void)
{
	t_list	*tokens;
//	t_token	token;

	tokens = NULL;  // ((4 + 9) * 5)
/*
	sh_populate_token(&token, OPN_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, OPN_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, INT, 4, TYPE_INT);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, PLUS, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, INT, 9, TYPE_INT);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, CLS_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, MULT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, INT, 5, TYPE_INT);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, CLS_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_parse_token_list(tokens);
*/
	sh_parse_token_list(tokens);
	return (0);
}

int		sh_init_pda_stack(t_list **stack, t_cfg *cfg)
{
	*stack = NULL;
	if (ft_lstaddnew_ptr_last(stack, cfg->symbols.tbl[S],
				sizeof(t_symbol *)))
		return (1);
	if (ft_lstaddnew_ptr_last(stack, cfg->symbols.tbl[END_OF_INPUT],
				sizeof(t_symbol *)))
		return (1);
	return (0);
}

int		process_ll_parsing(t_parser *parser)
{
	sh_init_pda_stack(&parser->pda_stack, &parser->cfg);
	sh_print_pda(parser->pda_stack);
	return (0);
}

int		sh_parse_token_list(t_list *tokens)
{
	t_parser parser;

	parser.tokens = tokens;
//	sh_print_token_list(parser.tokens);
	if (init_context_free_grammar(&parser.cfg))
		return (1);
	print_cfg(&parser.cfg);
	process_ll_parsing(&parser);
	return (0);
}
