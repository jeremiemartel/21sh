/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 12:22:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol)
{
	return (symbol->id >= 0 && symbol->id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_token_id id,
		int val, t_token_type type)
{
	token->token_union.ival = val;
	token->token_id = id;
	token->token_type = type;
}

t_production	*sh_production_lst_dup_ptr(t_list *symbols)
{
	t_production *res;
	t_list *ptr;

	if (!(res = (t_production *)malloc(sizeof(t_production))))
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

int		sh_add_prod_from_symbols(t_symbol *symbol, t_list *symbols)
{
	t_production *res;

	if (!(res = sh_production_lst_dup_ptr(symbols)))
		return (1);
	if (ft_lstaddnew_ptr_last(&symbol->productions, res,
		sizeof(t_production *)))
			return (1);
	return (0);
}

int		sh_add_prod(t_symbol *symbol, t_dy_tab symbols, int nb_symbols, ...)
{
	t_production *res;
	va_list		ap;
	int			symbol_index;
	t_symbol	**cfg_symbols;
	int 		i;

	cfg_symbols = (t_symbol **)symbols.tbl;
	if (!(res = (t_production *)malloc(sizeof(t_production))))
		return (1);
	if (ft_lstaddnew_ptr_last(&symbol->productions, res, sizeof(*res)))
		return (1);
	va_start(ap, nb_symbols);
	i = 0;
	res->symbols = NULL;
	while (i < nb_symbols)
	{
		symbol_index = va_arg(ap, int);
		if (ft_lstaddnew_ptr_last(&res->symbols, cfg_symbols[symbol_index],
				sizeof(t_symbol *)))
			return (1);
		i++;
	}
	va_end(ap);
	return (0);
}

void		sh_process_init_symbol(t_symbol *symbol, t_token_id id)
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
	symbol->splits = 0;
}

t_symbol	*new_symbol(t_token_id id)
{
	t_symbol	*symbol;
	
	if (!(symbol = (t_symbol *)malloc(sizeof(t_symbol))))
		return (NULL);
	sh_process_init_symbol(symbol, id);
	ft_strcpy(symbol->debug, g_grammar[id].debug);
	return (symbol);
}

t_symbol	*sh_new_symbol_from(t_symbol *from, t_token_id id)
{
	t_symbol	*symbol;
	char		*str;

	if (!(symbol = (t_symbol *)ft_memalloc(sizeof(t_symbol))))
		return (NULL);
	sh_process_init_symbol(symbol, id);
	if (!(str = ft_itoa(++from->splits)))
		return (symbol);
	ft_strcpy(symbol->debug, from->debug);
	ft_strlcat(symbol->debug, "(", sizeof(symbol->debug));
	ft_strlcat(symbol->debug, str, sizeof(symbol->debug));
	ft_strlcat(symbol->debug, ")", sizeof(symbol->debug));
	free(str);
	return (symbol);
}

void	ft_swap_first(t_symbol *symbol)
{
	t_list *tmp;
	t_list *tmp2;

	tmp = symbol->productions->next;
	tmp2 = symbol->productions->next->next;
	tmp->next = symbol->productions;

	symbol->productions = tmp;
	symbol->productions->next->next = tmp2;
}

int		init_context_free_grammar(t_cfg *cfg)
{
	int			i;
	int			ret;
	t_symbol	*new;

	cfg->start_index = PROGRAM;
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
	while (i < NB_SYMBOLS)
	{
		if (g_grammar[i].init_prod(cfg, ((t_symbol **)(cfg->symbols.tbl))[i]))
			return (1);
		i++;
	}
	sh_print_non_terminals_productions(cfg);
	while ((ret = sh_refine_grammar(cfg)) == 1)
		;
	sh_print_non_terminals_productions(cfg);
//	exit(0);
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
	if (ft_lstaddnew_ptr_last(stack, cfg->symbols.tbl[cfg->start_index],
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
