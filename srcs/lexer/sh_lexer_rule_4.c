/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:36:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/08 14:59:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		lexer_quoting_backslash(t_lexer *lexer)
{
	if (lexer->quoted == '\\')
	{
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		lexer->tok_len++;
		lexer->quoted = -lexer->quoted;
	}
	else
	{
		lexer->tok_len++;
		// ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		lexer->quoted = '\\';
	}
	return (LEX_OK);
}

static int		lexer_quoting_start_quote(t_lexer *lexer)
{
	lexer->quoted = lexer->c;
		lexer->tok_len++;
	// ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
	if (lexer->current_id == LEX_TOK_UNKNOWN)
		lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}

static int		lexer_quoting_simple_quote(t_lexer *lexer)
{
	if (lexer->c == '\'')
	{
		lexer->quoted = -lexer->quoted;
		lexer->tok_len++;
		// ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
	}
	else
		lexer->tok_len++;
	return (LEX_OK);
}

static int		lexer_quoting_double_quote(t_lexer *lexer)
{
	if (lexer->c == '$' || lexer->c == '`' || lexer->c == '\\')
		return (LEX_CONTINUE);
	if (lexer->c == '"')
	{
		lexer->quoted = -lexer->quoted;
		lexer->tok_len++;
		// ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
	}
	else
		lexer->tok_len++;
	return (LEX_OK);
}

// static int 		test(t_lexer *lexer)
// {
// 	if (lexer->c == lexer->quoted)
// 	{
// 		lexer->quoted = -lexer->quoted;
// 		if (lexer->current_id == LEX_TOK_UNKNOWN)
// 			lexer->current_id = LEX_TOK_WORD;
// 	}
// 	lexer->tok_len++;
// 	return (LEX_OK);
// }

int				sh_lexer_rule4(t_lexer *lexer)
{
	if (lexer->quoted != '\'' && (lexer->c == '\\' || lexer->quoted == '\\'))
		return (lexer_quoting_backslash(lexer));
	if (lexer->quoted <= 0 && (lexer->c == '\'' || lexer->c == '"'))
		return (lexer_quoting_start_quote(lexer));
	if (lexer->quoted == '\'')
		return (lexer_quoting_simple_quote(lexer));
	else if (lexer->quoted == '"')
		return (lexer_quoting_double_quote(lexer));
	// else
	// 	return (test(lexer));
	return (LEX_CONTINUE);
}
