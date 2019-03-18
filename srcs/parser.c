/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/18 07:07:42 by ldedier          ###   ########.fr       */
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


t_token *ntoken(int id)
{
	t_token *res;

	res = malloc(sizeof(t_token));
	res->token_id = id;
	return (res);
}


int		sh_init_ll_parsing(t_parser *parser) //to free if fail
{
	t_ast_node *node;
	t_ast_builder *ast_builder;

	parser->pda_stack = NULL;
	parser->root = NULL;
	if (!(node = sh_new_node(NULL)))
		return (1);
	if (sh_add_new_node(&parser->root, node))
		return (1);
	if (!(ast_builder = sh_new_ast_builder(&parser->root, &parser->cfg.symbols[E])))
		return (1);
	if (ft_lstaddnew_last(&parser->pda_stack, ast_builder, sizeof(t_ast_builder)))
		return (1);
	return (0);
}


t_list	*ft_lstdup_ast_builder(t_list *symbols, t_ast_node **parent_node)
{
	t_list			*res;
	t_list			*ptr;
	t_ast_builder	ast_builder;
	t_ast_node		*node;
	static int i = 0;

	i++;
	res = NULL;
	ptr = symbols;
	while (ptr != NULL)
	{
		ast_builder.symbol = (t_symbol *)ptr->content;
		ast_builder.node = NULL;
		if (ast_builder.symbol->relevant)
		{
			if (!ast_builder.symbol->replacing && !sh_is_term(ast_builder.symbol))
			{
				if (!(node = sh_new_node(NULL)))
					return (NULL);
				if (sh_add_new_node(parent_node, node))
					return (NULL);
				ast_builder.node = node;
			}
			else
				ast_builder.node = *parent_node;
		}
		if (ft_lstaddnew_last(&res, &ast_builder, sizeof(t_ast_builder)))
		{
			//ft_lstdel_ptr(&res);
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (res);
}

int		push_prod_to_stack(t_production *production, t_list **pda_stack, t_ast_node **parent_node)
{
	t_list *res;
	t_list *ptr;

	if (!(res = ft_lstdup_ast_builder(production->symbols, parent_node)))
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
	t_ast_builder	*ast_builder;
	t_production	*production;

	ft_printf("PREDICTION\n");
	if (!(ast_builder = ft_lstpop_ptr(&parser->pda_stack)))
		return (1);
	if ((production = parser->cfg.ll_table[ast_builder->symbol->id - NB_TERMS][token->token_id]))
	{
		if (push_prod_to_stack(production, &parser->pda_stack, &ast_builder->node))
			return (2);
	}
	else
		return (1);
	return (0);
}

int		sh_match(t_list **pda_ptr, t_list **tokens_ptr)
{
	t_token			*token;
	t_ast_builder	*ast_builder;

	if (*tokens_ptr == NULL)
		return (1);
	//	ft_printf("IT'S A MATCH\n");
	token = (*tokens_ptr)->content;
	*tokens_ptr = (*tokens_ptr)->next;
	if (!(ast_builder = ft_lstpop_ptr(pda_ptr)))
		return (1);
	if (token->token_id == ast_builder->symbol->id)
	{
		ft_printf("matching: ");
		sh_print_symbol(ast_builder->symbol);
		ft_printf("\n");
		if (ast_builder->symbol->relevant)
		{
			//(*(ast_builder->node))->token = token;
			ast_builder->node->token = token;
			ft_printf("YOPLAA\n");
		}
		return (0);
	}
	else
		return (1);
}

int		iz_okay_parsing(t_list *tokens)
{
	t_token *token;

	if (tokens == NULL)
		return (0);
	else
	{
		token = tokens->content;
		return (token->token_id == END_OF_INPUT);
	}
}

int		process_ll_parsing(t_parser *parser)
{
	t_ast_builder	*ast_builder;
	t_list			*tokens;

	tokens = parser->tokens;
	sh_init_ll_parsing(parser);
	sh_print_pda(parser->pda_stack);
	while (parser->pda_stack)
	{
		ast_builder = (t_ast_builder *)(parser->pda_stack->content);
		if (sh_is_term(ast_builder->symbol))
		{
			if (sh_match(&parser->pda_stack, &tokens))
				return (1);
		}
		else if (sh_predict(parser, (t_token *)tokens->content))
			return (1);
		sh_print_pda(parser->pda_stack);
		//		sh_print_token_list(tokens);
		//		sh_print_ast_parser(parser);
	}
	return (iz_okay_parsing(tokens) ? 0 : 1);
}

int		op_nothing(t_ast_node *node)
{
	(void)node;
	return (0);
}

int		op_plus(t_ast_node *node)
{
	return (traverse(node->children->content) + traverse(node->children->next->content));
}

int		op_mult(t_ast_node *node)
{
	return (traverse(node->children->content) * traverse(node->children->next->content));
}

int		op_int(t_ast_node *node)
{
	return (node->token->token_union.ival);
}

static  int (*g_operator_token[NB_TERMS - 1])
	(t_ast_node *) =
{
	op_nothing,
	op_nothing,
	op_plus,
	op_mult,
	op_int,
};

int		traverse(t_ast_node *node)
{
	return ((g_operator_token[node->token->token_id])(node));
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
		ft_printf(RED"syntaxical error\n"EOC);
		return (1);
	}
	else
	{
		ft_printf(GREEN"syntax OK\n"EOC);
		sh_print_ast_parser(&parser);
		ft_printf("%d\n", traverse(parser.root));
		return (0);
	}
}
