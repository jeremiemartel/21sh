/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/13 00:40:25 by ldedier          ###   ########.fr       */
/*                                                                            */
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

/*
 ** attributes for each non_terminal every single of its productions
 */

static	int (*g_init_grammar_productions[NB_NOTERMS])
	(t_cfg *, t_symbol *symbol) = 
{
	init_E,
	init_Op,
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
		"OP",
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
	ft_strcpy(symbol->debug, get_debug(id));
}

int		init_context_free_grammar(t_cfg *cfg)
{
	int i;
	int j;

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
	if (sh_compute_first_sets(cfg))
		return (1);
	if (sh_compute_follow_sets(cfg))
		return (1);
	if (sh_compute_ll_table(cfg))
		return (1);
	return (0);
}

int		sh_process_test(void)
{
	t_list	*tokens;
	t_token	token;

	tokens = NULL;  // ((4 + 9) * 5)
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
	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_parse_token_list(tokens);
	return (0);
}

int		sh_init_pda_stack(t_list **stack, t_cfg *cfg)
{
	*stack = NULL;
	if (ft_lstaddnew_ptr_last(stack, &cfg->symbols[E],
				sizeof(t_symbol *)))
		return (1);
	if (ft_lstaddnew_ptr_last(stack, &cfg->symbols[END_OF_INPUT],
				sizeof(t_symbol *)))
		return (1);
	return (0);
}

int		sh_match(t_list **pda_ptr, t_list **tokens_ptr)
{
	t_token *token;
	t_symbol *stack_symbol;

//	ft_printf("IT'S A MATCH\n");
	if (!(token = ft_lstpop_ptr(tokens_ptr)))
		return (1);
	if (!(stack_symbol = ft_lstpop_ptr(pda_ptr)))
		return (1);
	if (token->token_id == stack_symbol->id)
		return (0);
	else
		return (1);
}

t_list	*ft_lstdup_ptr(t_list *list)
{
	t_list *res;
	t_list *ptr;

	res = NULL;
	ptr = list;
	while (ptr != NULL)
	{
		if (ft_lstaddnew_ptr_last(&res, ptr->content, ptr->content_size))
		{
	//		ft_lstdel_ptr(&res);
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (res);
}

int		push_prod_to_stack(t_production *production, t_list **pda_stack)
{
	t_list *res;
	t_list *ptr;

	if (!(res = ft_lstdup_ptr(production->symbols)))
		return (1);
	ptr = res;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = *pda_stack;
	*pda_stack = res;
	return (0);
}

int		sh_predict(t_parser *parser, t_token *token)
{
	t_symbol		*stack_no_term;
	t_production	*production;

	ft_printf("PREDICTION\n");
	if (!(stack_no_term = ft_lstpop_ptr(&parser->pda_stack)))
		return (1);
	if ((production = parser->cfg.ll_table[stack_no_term->id - NB_TERMS][token->token_id]))
	{
		if (push_prod_to_stack(production, &parser->pda_stack))
			return (2);
	}
	else
		return (1);
	return (0);
}

int		process_ll_parsing(t_parser *parser)
{
	t_symbol	*symbol;

	sh_init_pda_stack(&parser->pda_stack, &parser->cfg);
	sh_print_pda(parser->pda_stack);
	while (parser->pda_stack)
	{
		symbol = (t_symbol *)(parser->pda_stack->content);
		if (sh_is_term(symbol))
		{
			if (sh_match(&parser->pda_stack, &parser->tokens))
				return (1);
		}
		else if (sh_predict(parser, (t_token *)parser->tokens->content))
			return (1);
		sh_print_pda(parser->pda_stack);
		sh_print_token_list(parser->tokens);
	}
	if (parser->tokens == NULL)
	{
		return (0);
	}
	else
		return (1);
}

int		sh_parse_token_list(t_list *tokens)
{
	t_parser parser;

	parser.tokens = tokens;
	sh_print_token_list(parser.tokens);
	if (init_context_free_grammar(&parser.cfg))
		return (1);
	print_cfg(&parser.cfg);
	if (process_ll_parsing(&parser))
	{
		ft_printf("syntaxical error\n");
		return (1);
	}
	else
		return (0);
}
