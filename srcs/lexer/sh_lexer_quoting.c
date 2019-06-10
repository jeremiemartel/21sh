/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:50:09 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 10:48:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		lexer_quoting_backslash(t_lexer *lexer)
{
	if (lexer->quoted == '\\')
	{
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		lexer->tok_len++;
		lexer->quoted = 0;
	}
	else
	{
		ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		lexer->quoted = '\\';
	}
	// if (lexer->input[lexer->tok_start + lexer->tok_len] == '\n')
	// {
	// 	ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
	// 	return (LEX_OK);
	// }
	return (LEX_OK);
}

int		lexer_quoting_start_quote(t_lexer *lexer)
{
	lexer->quoted = lexer->c;
	ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
	if (lexer->current_id == LEX_TOK_UNKNOWN)
		lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}

int		lexer_quoting_simple_quote(t_lexer *lexer)
{
	if (lexer->c == '\'')
	{
		lexer->quoted = 0;
		ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
	}
	else
		lexer->tok_len++;
	return (LEX_OK);
}

int		lexer_quoting_double_quote(t_lexer *lexer)
{
	if (lexer->c == '$' || lexer->c == '`' || lexer->c == '\\')
		return (LEX_CONTINUE);
	if (lexer->c == '"')
	{
		lexer->quoted = 0;
		ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
	}
	else
		lexer->tok_len++;
	return (LEX_OK);
}
