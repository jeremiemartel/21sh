/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:24:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/07 16:47:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp_init(char *original, t_expansion *exp)
{
	char	*start;

	exp->res = NULL;
	if (!(start = ft_strpbrk(original, "$~`")))
		return (LEX_ERR);
	if (*start == '`')
		sh_exp_init_detect_pattern(exp, start, "`", LEX_EXP_CMD);
	else if (ft_strnstr(start, "$((", 3))
		sh_exp_init_detect_pattern(exp, start, "))", LEX_EXP_ARITH);
	else if (ft_strnstr(start, "$(", 2))
		sh_exp_init_detect_pattern(exp, start, ")", LEX_EXP_CMD);
	else if (ft_strnstr(start, "${", 2))
		sh_exp_init_detect_pattern(exp, start, "}", LEX_EXP_PARAM);
	else if (ft_strnstr(start, "$", 1))
		sh_exp_init_detect_chars(exp, start, " \t\n\0", LEX_EXP_VAR);
	else if (ft_strnstr(start, "~", 1))
		sh_exp_init_detect_chars(exp, start, "/ \t\n\0", LEX_EXP_TILDE);
	else
		return (LEX_ERR);
	if (sh_lexer_exp_init_process(exp) == LEX_ERR)
		return (LEX_ERR);
	return (LEX_OK);
}

int			sh_exp_init_detect_pattern(t_expansion *exp, char *start, char *pattern, int type)
{
	char	*end;

	exp->type = type;
	if (!(end = ft_strstr(start, pattern)))
		return (LEX_ERR);
	end += ft_strlen(pattern);
	if (!(exp->original = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_pattern (1)"));
	if (*start == '$' && (start[1] == '(' || start[1] == '{'))
	{
		start += 2;
		if (*start == '(')
			start++;
	}
	else
		start++;
	if (!(exp->expansion = ft_strndup(start, end -ft_strlen(pattern) - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_pattern (2)"));
	return (LEX_OK);
}

int			sh_exp_init_detect_chars(t_expansion *exp, char *start, char *pattern, int type)
{
	char	*end;

	exp->type = type;
	if (!(end = ft_strpbrk(start, pattern)) && !(end = ft_strchr(start, '\0')))
		return (LEX_ERR);
	if (!(exp->original = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_chars (1)"));
	start++;
	if (!(exp->expansion = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_chars (2)"));
	return (LEX_OK);
}

int		sh_lexer_exp_init_process(t_expansion *exp)
{
	if (exp->type == LEX_EXP_VAR)
		exp->process = &sh_lexer_exp_variable;
	else if (exp->type == LEX_EXP_PARAM)
		exp->process = &sh_lexer_exp_parameter;
	else if (exp->type == LEX_EXP_CMD)
		exp->process = &sh_lexer_exp_command;
	else if (exp->type == LEX_EXP_ARITH)
		exp->process = &sh_lexer_exp_arithmetic;
	else if (exp->type == LEX_EXP_TILDE)
		exp->process = &sh_lexer_exp_tilde;
	else
		return (LEX_ERR);
	return (LEX_OK);
	(void)exp;
}
