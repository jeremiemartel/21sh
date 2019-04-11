/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/03 17:18:44 by ldedier          ###   ########.fr       */
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

void	sh_create_moke_list(t_list **tokens)
{
	t_token	token;

	*tokens = NULL;  // ((4 + 9) * 5) = 65
/*
sh_populate_token(&token, T_A, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
	sh_populate_token(&token, T_B, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
*/
	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(tokens, &token, sizeof(t_token));
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
		sh_print_ast_parser(parser);
		ft_printf("%d\n", sh_traverse(parser->root));
	}
	return (0);
}

int		sh_process_test(void)
{
	t_lr_parser parser;
	t_list	*tokens;

	sh_create_moke_list(&tokens);
	if (init_parsing(&parser))
		return (1);
	parser.tokens = tokens;
	sh_print_parser(&parser, 0);
	sh_parse_token_list(&parser);
	return (0);
}
