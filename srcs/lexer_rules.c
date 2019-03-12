/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:36:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/12 19:31:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

// char	g_quotes[] =  "`'\"";
# define	LEX_OPERATOR_TAB "|&;<>()"

int		lex_rules_is_valid_operator(int op)
{
	if (op == LEX_TOK_AND_IF ||
		op == LEX_TOK_OR_IF ||
		op == LEX_TOK_DSEMI ||
		op == LEX_TOK_DLESS ||
		op == LEX_TOK_DGREAT ||
		op == LEX_TOK_LESSAND ||
		op == LEX_TOK_GREATAND ||
		op == LEX_TOK_LESSGREAT ||
		op == LEX_TOK_DLESSDASH ||
		op == LEX_TOK_CLOBBER ||
		op == LEX_TOK_PIPE ||
		op == LEX_TOK_AND ||
		op == LEX_TOK_SEMICOL ||
		op == LEX_TOK_LESS ||
		op == LEX_TOK_GREAT)
		return (1);
	return (0);
}

int		lexer_rule1(t_lexer *lexer)
{
	if (lexer->c == LEX_TOK_NEWLINE || lexer->c == '\0')//
	{
		lexer_add_token(lexer);
		return (LEX_END);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule2(t_lexer *lexer)
{
	static char		operators[] = LEX_OPERATOR_TAB;

	if (lexer->quoted)
		return (LEX_CONTINUE);
	if (!ft_strchr(operators, lexer->current_id & 0x00ff))
		return (LEX_CONTINUE);
	if (ft_strchr(operators, lexer->c))
	{
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = lexer->c;
		else if (!(lexer->current_id & 0xff00))
			lexer->current_id += 0xff00 * lexer->c;
		else
			lexer->current_id += 0xff0000 * lexer->c;		
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule3(t_lexer *lexer)
{
	static char		operators[] = LEX_OPERATOR_TAB;

	if (!lexer->current_id ||  !(ft_strchr(operators, lexer->current_id & 0x00ff)))
		return (LEX_CONTINUE);
	if (!ft_strchr(operators, lexer->c))
	{
		if (lex_rules_is_valid_operator(lexer->current_id))
		{
			lexer_add_token(lexer);
			lexer->tok_len = 0;
			return (LEX_OK);
		}
		return (LEX_ERR);//
	}
	return (LEX_CONTINUE);
}

int		lexer_rule6(t_lexer *lexer)
{
	static char		operators[] = LEX_OPERATOR_TAB;

	if (!lexer->quoted && ft_strchr(operators, lexer->c))
	{
		lexer_add_token(lexer);
		lexer->tok_len = 1;
		lexer->current_id = lexer->c & 0x00ff;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule7(t_lexer *lexer) // Need to add quoted option
{
	if (lexer->c == LEX_TOK_SPACE && lexer->quoted == LEX_TOK_UNKNOWN)
	{
		lexer_add_token(lexer);
		lexer->tok_start++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule8(t_lexer *lexer)
{
	if (lexer->current_id == LEX_TOK_WORD)
	{
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule9(t_lexer *lexer)
{
	if (lexer->c == '#')
	{
		if (!ft_strchr(lexer->input + lexer->tok_start , '\n'))
			lexer->input[lexer->tok_start] = 0;
		else
			ft_strcpy(lexer->input + lexer->tok_start, ft_strchr(lexer->input + lexer->tok_start , '\n'));
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule10(t_lexer *lexer)
{
	lexer->tok_len = 1;
	lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}
