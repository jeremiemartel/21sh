/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_detect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:54:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/21 18:38:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		lexer_expansion_fill_pattern(t_expansion *expansion, char *start, char *end, int len)
{
	ft_strcpy(expansion->pattern.start, start);
	ft_strcpy(expansion->pattern.end, end);
	expansion->pattern.len_s = len % 10;
	expansion->pattern.len_e = len / 10;
}

int			lexer_expansion_detect(char *input, t_expansion *expansion)
{
	if (*input == '`')
		return (lexer_expansion_detect_command(input, expansion));
	else if (ft_strnstr(input, "$((", 3))
		return (lexer_expansion_detect_arithmetic(input, expansion));
	else if (ft_strnstr(input, "$(", 2))
		return (lexer_expansion_detect_command(input, expansion));
	else if (ft_strnstr(input, "${", 2))
		return (lexer_expansion_detect_parameter(input, expansion));
	else if (ft_strnstr(input, "$", 1))
		return (lexer_expansion_detect_variable(input, expansion));
	else
	{
		ft_putstrn("\033[31mNo expansions detectd in expasion_detect%s\033[0m");//
		return (LEX_EXP_ERR);
	}
	return (LEX_EXP_ERR);
}

int			lexer_expansion_detect_command(char *input, t_expansion *expansion)
{
	expansion->type = LEX_EXP_CMD;
	expansion->res = NULL;
	if (*input == '`')
	{
		if (!(ft_strchr(input + 1, '`')))
			return (LEX_EXP_ERR);
		expansion->original = ft_strndup(input, ft_strchr(input + 1, '`') - input + 1); //+1 ??
		expansion->expansion = ft_strndup(input + 1, ft_strchr(input + 1, '`') - (input + 1));
		lexer_expansion_fill_pattern(expansion, "`", "`", 1 + 10 * 1);
		ft_printf("creating expansion : \n\texpansion : %s\n", expansion->expansion);
	}
	else
	{
		if (!(ft_strchr(input + 2, ')')))
			return (LEX_EXP_ERR);
		expansion->original = ft_strndup(input, ft_strchr(input + 2, ')') - input + 1); //+1?
		expansion->expansion = ft_strndup(input + 2, ft_strchr(input + 2, ')') - (input + 2));
		lexer_expansion_fill_pattern(expansion, "$(", ")", 2 + 10 * 1);
	}
	if (!expansion->original || !expansion->expansion)
	{
		if (expansion->original)
			free(expansion->original);
		if (expansion->expansion)
			free(expansion->expansion);
		return (LEX_EXP_ERR);
	}
	ft_printf("detecting command : \n\toriginal : %s\n\texpansion: %s\n", expansion->original, expansion->expansion);
	return (LEX_EXP_OK);
}

int			lexer_expansion_detect_arithmetic(char *input, t_expansion *expansion)
{
	expansion->type = LEX_EXP_ARITH;
	expansion->res = NULL;
	if (!(ft_strchr(input + 3, ')')))
		return (LEX_EXP_ERR);
	expansion->original = ft_strndup(input, ft_strchr(input + 3, ')') - input + 1);
	expansion->expansion = ft_strndup(input + 3, ft_strchr(input + 3, ')') - (input + 3));
	if (!expansion->original || !expansion->expansion)
	{
		if (expansion->original)
			free(expansion->original);
		if (expansion->expansion)
			free(expansion->expansion);
		return (LEX_EXP_ERR);
	}
	lexer_expansion_fill_pattern(expansion, "$((", ")", 3 + 10 * 1);
	ft_printf("detecting arithmetic : \n\toriginal : %s\n\texpansion: %s\n", expansion->original, expansion->expansion);
	return (LEX_EXP_OK);
	(void)expansion;
	(void)input;
}

int			lexer_expansion_detect_parameter(char *input, t_expansion *expa)
{
	char	*start;

	expa->type = LEX_EXP_PARAM;
	lexer_expansion_fill_pattern(expa, "${", "}", 2 + 10 * 1);
	if (!(start = ft_strpbrk(input + expa->pattern.len_s, expa->pattern.end)))
		return (LEX_EXP_ERR);
	expa->original = ft_strndup(input, start - input + 1);
	expa->expansion = ft_strndup(input + expa->pattern.len_s, start - (input - expa->pattern.len_s));
	if (!expa->original || !expa->expansion)
	{
		if (expa->original)
			free(expa->original);
		if (expa->expansion)
			free(expa->expansion);
		return (LEX_EXP_ERR);
	}
	lexer_expansion_fill_pattern(expa, "$((", ")", 3 + 10 * 1);
	ft_printf("detecting arithmetic : \n\toriginal : %s\n\texpansion: %s\n", expa->original, expa->expansion);
	return (LEX_EXP_OK);
}

int			lexer_expansion_detect_variable(char *input, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)expansion;
	(void)input;
}
