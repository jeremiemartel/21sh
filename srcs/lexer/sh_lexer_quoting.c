/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:50:09 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 11:04:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		lexer_quoting_backslash(t_lexer *lexer)
{
	ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
	if (lexer->input[lexer->tok_start + lexer->tok_len] == '\n')
	{
		ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		return (LEX_OK);
	}
	if (lexer->current_id == LEX_TOK_UNKNOWN)
		lexer->current_id = LEX_TOK_WORD;
	lexer->tok_len++;
	return (LEX_OK);
}

int		lexer_quoting_double_quote(t_lexer *lexer)
{
	return (SUCCESS);
	(void)lexer;
}

int		lexer_quoting_simple_quote(t_lexer *lexer)
{
	return (SUCCESS);
	(void)lexer;
}
