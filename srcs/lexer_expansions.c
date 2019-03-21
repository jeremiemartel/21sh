/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:40:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/21 12:32:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_replace(t_expansion *expansion, char **input)
{
	*input = ft_strrep_free(*input, expansion->res->str, expansion->original, 1);
	if (!(*input))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
}

void		lexer_expansion_free(t_expansion *expansion)
{
	if (expansion->original)
		free(expansion->original);
	if (expansion->expansion)
		free(expansion->expansion);
	if (expansion->res)
		ft_dystr_free(expansion->res);
}

int			lexer_expansion(t_lexer *lexer, char **input)
{
	t_expansion		expansion;
	char			*buffer;

	//First  call to recursive function
	ft_putstrn("\n");
	if (input == &lexer->input)
	{
		if (!(buffer = ft_strdup(lexer->input + lexer->tok_start + lexer->tok_len)))
			return (LEX_EXP_ERR);
	}
	else
		buffer = *input;
	ft_printf("Initial expansion : %s\n", buffer);
	if (lexer_expansion_detect(buffer, &expansion) == LEX_EXP_ERR)
		return (LEX_EXP_ERR);
	if (input == &lexer->input)
		free(buffer);
	lexer_expansion_process(lexer, &expansion);
	if (lexer_expansion_replace(&expansion, input) == LEX_EXP_ERR)
		return (LEX_EXP_ERR);
	ft_printf("expansion processed res : %s\n", expansion.res->str);
	ft_printf("expansion output : %s\n", *input);
	lexer->tok_len += ft_strlen(expansion.res->str);
	lexer_expansion_free(&expansion);
	return (LEX_EXP_OK);
	(void)input;
	(void)lexer;
}















/*
int			lexer_expansion_identify(char *input, t_expansion *expansion)
{
	if (!(expansion->dystr = ft_dystr_new(NULL, 0, 0)))
		return (LEX_EXP_ERR);
	if (*input == '`')
	{
		// ft_strcpy(expansion->pattern, "`");
		// expansion->exp_type = LEX_EXP_CMD;
		return (LEX_EXP_ERR);
	}
	else if (ft_strnstr(input, "$((", 3))
	{
		// ft_strcpy(expansion->pattern, "))");
		// expansion->exp_type = LEX_EXP_ARITH;
		return (LEX_EXP_ERR);
	}
	else if (ft_strnstr(input, "$(", 2))
	{
		// ft_strcpy(expansion->pattern, ")");
		// expansion->exp_type = LEX_EXP_CMD;
		return (LEX_EXP_ERR);
	}
	else if (ft_strnstr(input, "${", 2))
	{
		ft_strcpy(expansion->endpattern, "}");
		expansion->exp_type = LEX_EXP_PARAM;
		expansion->original = ft_strndup(input, ft_strstr(input, expansion->endpattern) - input + 1);
		expansion->dystr->str = ft_strndup(input + 2, ft_strstr(input, expansion->endpattern) - (input + 2));
		expansion->dystr->size = ft_strlen(expansion->dystr->str);
		expansion->dystr->len = expansion->dystr->size;
		return (LEX_EXP_OK);
	}
	else if (ft_strnstr(input, "$", 1))
	{
		// ft_strcpy(expansion->pattern, "");
		// expansion->exp_type = LEX_EXP_VAR;
		return (LEX_EXP_ERR);
	}
	else
		return (LEX_EXP_ERR);
}

int         lexer_expansion(char *input, t_lexer *lexer)
{
	t_expansion		expansion;
	char			*buf;

	if (lexer_expansion_identify(input, &expansion) == LEX_EXP_ERR)
	{
		free(expansion.original);
		ft_dystr_free(expansion.dystr);
		return (LEX_EXP_ERR);
	}
	ft_printf("lexer expansion dystr : %s\n", expansion.dystr->str);
	while ((buf = ft_strchr(expansion.dystr->str, '$')) || (buf = ft_strchr(expansion.dystr->str, '`')))
	{
		ft_putstrn("while check 0\n");
		if (*buf == '$')
			expansion.dystr->size = lexer_expansion(ft_strchr(expansion.dystr->str, '$'), lexer);
		else
			expansion.dystr->size = lexer_expansion(ft_strchr(expansion.dystr->str, '`'), lexer);
		if (expansion.dystr->size == LEX_EXP_ERR)
		{
			free(expansion.original);
			ft_dystr_free(expansion.dystr);
			return (LEX_EXP_ERR);
		}
	}
	ft_putstrn("lexer_expansion check 4");
	if (lexer_expansion_process(&expansion, lexer) == LEX_EXP_ERR)
	{
		ft_putstrn("lexer_expansion error (1)");
		ft_dystr_free(expansion.dystr);
		free(expansion.original);
		return (LEX_EXP_ERR);
	}
	ft_putstrn("lexer_expansion check 5");
	// pattern = ft_strndup(input, ft_strstr(input, expansion.pattern) - input);
	ft_printf("pattern for replace : %s\n", expansion.original);
	lexer->input = ft_strrep_free(input, expansion.dystr->str, expansion.original, 0x0001 + 0x0004);
	ft_printf("new lexer->input : %s\n", lexer->input);
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
	free(expansion->dystr->str);
	expansion->dystr->str = ft_strdup("parameter");
	expansion->dystr->len = ft_strlen(expansion->dystr->str);
	expansion->dystr->size = ft_strlen(expansion->dystr->str);
    return (expansion->dystr->size);
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
*/