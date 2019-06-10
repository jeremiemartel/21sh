/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 11:16:20 by ldedier          ###   ########.fr       */
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
	token->value = NULL;
}

int		sh_parse_token_list(t_lr_parser *parser)
{
	int ret;

	sh_free_parser_trees(parser);
	if ((ret = sh_lr_parse(parser)) != SUCCESS)
		return (ret);
	else
	{
		if (sh_verbose_ast())
		{
			ft_printf("OK !\n");
			ft_printf("\nAST:\n");
			sh_print_ast(parser->ast_root, 0);
		}
		return (SUCCESS);
	}
}

int		sh_parser(t_list *tokens, t_shell *shell)
{
	t_token token;
	int		ret;

	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	ft_lstdel(&shell->parser.tokens, sh_free_token_lst);
	if (sh_verbose_ast())
	{
		ft_printf("input tokens: ");
		sh_print_token_list(tokens, &shell->parser.cfg);
	}
	shell->parser.tokens = tokens;
	if ((ret = sh_parse_token_list(&shell->parser)) == 2)
		ft_dprintf(2, "syntax error\n");
	return (ret);
}
