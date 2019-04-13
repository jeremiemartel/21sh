/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 16:02:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol)
{
	return (symbol->id >= 0 && symbol->id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_symbol_id id,
		int val, t_token_type type)
{
	token->token_union.ival = val;
	token->id = id;
	token->index = sh_index(id);
	token->token_type = type;
}

int	sh_parse_token_list(t_lr_parser *parser)
{
	if (sh_lr_parse(parser))
	{
		ft_printf("LEXICAL ERROR\n");
		return (1);
	}
	else
	{
		ft_printf("OK !\n");
	//	sh_print_ast(parser->ast_node, 0);
		sh_print_ast(parser->cst_root, 0);
	//	ft_printf("%d\n", sh_traverse(parser->root));
	}
	return (0);
}

int		sh_parser(t_list *tokens)
{
	t_lr_parser parser;
	t_token token;

	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));

	if (init_parsing(&parser))
		return (1);
	parser.tokens = tokens;
	sh_print_token_list(tokens, &parser.cfg);
	sh_parse_token_list(&parser);
	return (0);
}
