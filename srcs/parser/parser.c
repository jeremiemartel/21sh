/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/11 19:08:39 by ldedier          ###   ########.fr       */
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
	if (sh_lr_parse(parser) != SUCCESS)
	{
		ft_printf("LEXICAL ERROR\n");
		return (FAILURE);
	}
	else
	{
		if (sh_verbose_ast())
		{
			ft_printf("OK !\n");
			ft_printf("\nAST:\n");
			sh_print_ast(parser->ast_root, 0);
			// ft_printf("\n\nCST:\n");
			// sh_print_ast(parser->cst_root, 0);
		}
		return (SUCCESS);

	}
}

int		sh_parser(t_list *tokens, t_shell *shell)
{
	t_token token;

	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	shell->parser.tokens = tokens;
	return (sh_parse_token_list(&shell->parser));
}
