/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_expansions_detect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:54:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 10:49:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** lexer_expansion_detect:
**		Function used to fill the t_expansion struct, detecting the current
**		expansion
*/
int			lexer_expansion_detect(char *input, t_expansion *exp)
{
	if (*input == '`')
		lexer_expansion_detect_fill_pattern(exp, "`", "`", 1 + 10 * 1 + 100 * LEX_EXP_CMD);
	else if (ft_strnstr(input, "$((", 3))
		lexer_expansion_detect_fill_pattern(exp, "$((", ")", 3 + 10 * 1 + 100 * LEX_EXP_ARITH);
	else if (ft_strnstr(input, "$(", 2))
		lexer_expansion_detect_fill_pattern(exp, "$(", ")", 2 + 10 * 1 + 100 * LEX_EXP_CMD);
	else if (ft_strnstr(input, "${", 2))
		lexer_expansion_detect_fill_pattern(exp, "${", "}", 2 + 10 * 1 + 100 * LEX_EXP_PARAM);
	else if (ft_strnstr(input, "$", 1))
		lexer_expansion_detect_fill_pattern(exp, "$", " \t\n\0", 1 + 10 * 0 + 100 * LEX_EXP_VAR);
	else if (ft_strnstr(input, "~", 1))
		lexer_expansion_detect_fill_pattern(exp, "~", "/ \t\n\0", 1 + 10 * 0 + 100 * LEX_EXP_TILDE);
	else
	{
		ft_putstrn("\033[31mNo expansions detected in lexer_expasion_detect\033[0m");//
		return (LEX_ERR);
	}
	return (lexer_expansion_detect_fill_expansion(input, exp));
}

/*
** lexer_expansion_detect_fill_pattern :
**		Fill the t_pattern struct according to detected expansion
*/
void		lexer_expansion_detect_fill_pattern(t_expansion *expansion, char *start, char *end, int len)
{
	expansion->type = len / 100;
	ft_strcpy(expansion->pattern.start, start);
	ft_strcpy(expansion->pattern.end, end);
	expansion->pattern.len_s = len % 10;
	expansion->pattern.len_e = len / 10;
}

/*
** lexer_expansion_detect_fill_expansion:
**		Fill the t_expansion struct according to detected expansion
*/
int			lexer_expansion_detect_fill_expansion(char *input, t_expansion *exp)
{
	char	*start;

	if (!(start = ft_strpbrk(input + exp->pattern.len_s, exp->pattern.end)))
		return (LEX_ERR);
	if (!(exp->original = ft_strndup(input, start - input + 1)))
		return (LEX_ERR);
	return (LEX_OK);
}
