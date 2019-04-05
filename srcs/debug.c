/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:04:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/04 19:41:25 by ldedier          ###   ########.fr       */
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

void	sh_print_token(t_token *token)
{
	if (token->token_type == TYPE_INT)
		ft_printf("%d", token->token_union.ival);
	else
	{
		if (token->token_id == PLUS)
			ft_printf("+");
		else if (token->token_id == OPN_PARENT)
			ft_printf("(");
		else if (token->token_id == CLS_PARENT)
			ft_printf(")");
		else if (token->token_id == END_OF_INPUT)
			ft_printf("$");
		else if (token->token_id == E)
			ft_printf("E");
		else if (token->token_id == INT)
			ft_printf("INT");
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
	sh_print_symbol(production->from);
	ft_printf(" → ");
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
		sh_print_symbol(&(cfg->symbols[i]));
		ft_printf(" : \n");
		print_non_terminal_production(&cfg->symbols[i++]);
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
			sh_print_symbol(&cfg->symbols[i]);
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
		sh_print_follow_set(cfg, &cfg->symbols[i++]);
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
		sh_print_first_set(cfg, &cfg->symbols[i++]);
		j++;
	}
}
/*
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
void	sh_print_ast(t_ast_node *node, int depth)
{
	t_list *ptr;
	int i;

	i = depth;
	if (!node)
	{
		ft_printf("LEAF NODE\n");
		return ;
	}
	while (i--)
		ft_printf("\t");
	if (node->token)
		sh_print_token(node->token);
	else
		ft_printf("NOT A TOKEN YET");
	ft_printf("\n");
	ptr = node->children;
	if (ptr)
		ft_printf("children:\n");
	i = 0;
	while (ptr != NULL)
	{
		ft_printf("child #%d: ", ++i);
		sh_print_ast(ptr->content, depth + 1);
		ft_printf("\n");
		ptr = ptr->next;
	}
}

void	sh_print_ast_parser(t_parser *parser)
{
	ft_printf(GREEN"//////////START AST///////////\n"EOC);
	sh_print_ast(parser->root, 0);
	ft_printf(RED"//////////END AST///////////\n"EOC);
}

void	sh_print_pda(t_list *stack)
{
	ft_printf("PDA STACK:\t");
	t_ast_builder	*ast_builder;
	t_list			*ptr;

	ptr = stack;
	while (ptr != NULL)
	{
		ast_builder = (t_ast_builder *)ptr->content;
		if (ptr != stack)
			ft_printf(" ");
		sh_print_symbol(ast_builder->symbol);
//		if (!ast_builder->node)
//			ft_printf("node: address: %p\n", NULL);
//		else
//			ft_printf("node: address: %p\n", ast_builder->node);
		ptr = ptr->next;
	}
	ft_printf("\n");
}
*/

void	sh_print_item(t_item *item)
{
	t_list		*ptr;
	t_symbol	*symbol;

	sh_print_symbol(item->production->from);
	ft_printf(" → ");
	ptr = item->production->symbols;
	while (ptr != NULL)
	{
		if (ptr == item->progress)
			ft_printf(BOLD"·"EOC);
		symbol = (t_symbol *)ptr->content;
		sh_print_symbol(symbol);
		ptr = ptr->next;
//		ft_printf(" ");
	}
	if (ptr == item->progress)
		ft_printf(BOLD"·"EOC);
	ft_printf("\t(for symbol: [");
	sh_print_symbol(item->lookahead);
	ft_printf("])\n");
}

void	sh_print_transition(t_transition *transition, int depth)
{
	sh_print_symbol(transition->symbol);
	ft_printf(" → ");
	sh_print_state(transition->state, depth);
}

void	sh_print_state(t_state *state, int depth)
{
	t_list			*ptr;
	t_item			*item;
	t_transition	*transition;

	ft_printf(YELLOW"State #%d\n\n"EOC, state->number);
	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		sh_print_item(item);
		ptr = ptr->next;
	}
	if (depth > 0 && state->transitions)
	{
		ft_printf(UNDERLINE"\nState transitions:%s \n\n", EOC);
		ptr = state->transitions;
		while (ptr != NULL)
		{
			transition = (t_transition *)ptr->content;
			sh_print_transition(transition, depth - 1);
			ptr = ptr->next;
		}
	}
}

void	sh_print_lr_table(t_lr_parser *parser)
{
	(void)parser;
}

void	sh_print_automata(t_lr_parser *parser, int depth)
{
	t_list	*ptr;
	t_state	*state;

	ft_printf(BOLD UNDERLINE"AUTOMATA STATES:\n\n"EOC);
	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		sh_print_state(state, depth);
		ft_printf("/////////////////////////////////\n");
		ptr = ptr->next;
	}
}

void	print_cfg(t_cfg *cfg)
{
	print_non_terminals_productions(cfg);
	print_first_sets(cfg);
	print_follow_sets(cfg);
}

void	sh_print_parser(t_lr_parser *parser, int depth)
{
	print_cfg(&parser->cfg);
	sh_print_automata(parser, depth);
	sh_print_lr_table(parser);
}
