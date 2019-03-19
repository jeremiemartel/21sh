/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:40:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 12:13:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_identify(char *input, t_expansion *expansion)
{
	if (*input == '`')
	{
		ft_strcpy(expansion->pattern, "`");
		expansion->exp_type = LEX_EXP_CMD;
	}
	else if (ft_strnstr(input, "$((", 3))
	{
		ft_strcpy(expansion->pattern, "))");
		expansion->exp_type = LEX_EXP_ARITH;
	}
	else if (ft_strnstr(input, "$(", 2))
	{
		ft_strcpy(expansion->pattern, ")");
		expansion->exp_type = LEX_EXP_CMD;
	}
	else if (ft_strnstr(input, "${", 2))
	{
		ft_strcpy(expansion->pattern, "}");
		expansion->exp_type = LEX_EXP_PARAM;
	}
	else if (ft_strnstr(input, "$", 1))
	{
		ft_strcpy(expansion->pattern, NULL);
		expansion->exp_type = LEX_EXP_VAR;
	}
	else
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
}

int			lexer_expansion_create_dystr(char *input, t_expansion *expansion)
{
	int		len;

	len = ft_strstr(input, expansion->pattern) - input;
	if (len <= 0)
		return (LEX_EXP_ERR);
	if (!(expansion->dystr = ft_dystr_new(input, 2 * len, len)))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
}

int         lexer_expansion(char *input, t_lexer *lexer)
{
	t_expansion		expansion;
	char			*pattern;
	char			*buf;

	if (lexer_expansion_identify(input, &expansion) == LEX_ERR)
		return (LEX_EXP_ERR);
	lexer_expansion_create_dystr(input, &expansion);
	while ((buf = ft_strchr(expansion.dystr->str, '$')) || (buf = ft_strchr(expansion.dystr->str, '`')))
	{
		if (*buf == '$')
			expansion.dystr->size = lexer_expansion(ft_strchr(expansion.dystr->str, '$'), lexer);
		else
			expansion.dystr->size = lexer_expansion(ft_strchr(expansion.dystr->str, '`'), lexer);
		if (expansion.dystr->size == LEX_EXP_ERR)
		{
			ft_dystr_free(expansion.dystr);
			return (LEX_EXP_ERR);
		}
	}
	if (lexer_expansion_process(&expansion, lexer) == LEX_EXP_ERR)
	{
		ft_dystr_free(expansion.dystr);
		return (LEX_EXP_ERR);
	}
	pattern = ft_strndup(input, ft_strstr(input, expansion.pattern) - input);
	input = ft_strrep_free(input, expansion.dystr->str, pattern, 0x0001 + 0x0004);
	ft_dystr_free(expansion.dystr);
	return (expansion.dystr->size);
}

int			lexer_expansion_process(t_expansion *expansion, t_lexer *lexer)
{
	if (expansion->exp_type == LEX_EXP_VAR)
		return (lexer_variable_expansion(expansion, lexer));
	if (expansion->exp_type == LEX_EXP_PARAM)
		return (lexer_parameter_expansion(expansion, lexer));
	if (expansion->exp_type == LEX_EXP_CMD)
		return (lexer_command_substitution(expansion, lexer));
	if (expansion->exp_type == LEX_EXP_ARITH)
		return (lexer_arithmetic_expression(expansion, lexer));
	return (LEX_EXP_ERR);
}

int			lexer_variable_expansion(t_expansion *expansion, t_lexer *lexer)
{
	ft_putstrn("variable expansion");
    return (LEX_EXP_ERR);
    (void)lexer;
	(void)expansion;
}

int         lexer_parameter_expansion(t_expansion *expansion, t_lexer *lexer)
{
    ft_putstrn("parameter expansion");
    return (LEX_EXP_ERR);
    (void)lexer;
	(void)expansion;
}

int         lexer_arithmetic_expression(t_expansion *expansion, t_lexer *lexer)
{
    ft_putstrn("arithmetic expression");
    return (LEX_EXP_ERR);
    (void)lexer;
	(void)expansion;
}

int         lexer_command_substitution(t_expansion *expansion, t_lexer *lexer)
{
    ft_putstrn("command substitution");
    return (LEX_EXP_ERR);
    (void)lexer;
	(void)expansion;
}
