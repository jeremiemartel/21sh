/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:24:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/05 13:53:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_init:
**	take an input as a string and a expansion. The expansion is filled with
**	the first expansion found in input.
**	Exp fields filled: type, original, expansion, process
**	Return Value:
**		FAILURE or SUCCESS
*/
int		sh_expansions_init(char *original, t_expansion *exp)
{
	char	*start;

	exp->res = NULL;
	if (!(start = ft_strpbrk(original, "$~`")))
		return (FAILURE);
	// if (*start == '`')
	// 	sh_exp_init_detect_pattern(exp, start, "`", EXP_CMD);
	// else if (ft_strnstr(start, "$((", 3))
	// 	sh_exp_init_detect_pattern(exp, start, "))", EXP_ARITH);
	// else if (ft_strnstr(start, "$(", 2))
	// 	sh_exp_init_detect_pattern(exp, start, ")", EXP_CMD);
	if (ft_strnstr(start, "${", 2))
		sh_exp_init_detect_pattern(exp, start, "}", EXP_PARAM);
	else if (ft_strnstr(start, "$", 1))
		sh_exp_init_detect_chars(exp, start, " \t\n\0", EXP_VAR);
	else if (ft_strnstr(start, "~", 1))
		sh_exp_init_detect_chars(exp, start, " \t\n\0", EXP_TILDE);
	else
		return (FAILURE);
	if (sh_expansions_init_process(exp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/*
** sh_exp_init_detect_pattern:
**		Use the type of detected expansion to fill original and expansion fields in exp
**		End of expansion is a strind used as a pattern.
**		Return Value:
**			SUCCESS or FAILURE
*/
int			sh_exp_init_detect_pattern(t_expansion *exp, char *start, char *pattern, int type)
{
	char	*end;

	exp->type = type;
	if (!(end = ft_strstr(start, pattern)))
		return (FAILURE);
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
	return (SUCCESS);
}

/*
** sh_exp_init_detect_chars:
**		Use the type of detected expansion to fill original and expansion fields in exp
**		End of expansion is one of the character given in pattern.
**		Return Value:
**			SUCCESS or FAILURE
*/
int			sh_exp_init_detect_chars(t_expansion *exp, char *start, char *pattern, int type)
{
	char	*end;

	exp->type = type;
	if (!(end = ft_strpbrk(start, pattern)) && !(end = ft_strchr(start, '\0')))
		return (FAILURE);
	if (!(exp->original = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_chars (1)"));
	start++;
	if (!(exp->expansion = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_chars (2)"));
	return (SUCCESS);
}

/*
** sh_expansions_init_process:
**		fill the process exp's field using it's type
**	Return Value:
**		FAILURE: type is unknow
**		SUCCESS: else
*/
int		sh_expansions_init_process(t_expansion *exp)
{
	if (exp->type == EXP_VAR)
		exp->process = &sh_expansions_variable;
	else if (exp->type == EXP_PARAM)
		exp->process = &sh_expansions_parameter;
	// else if (exp->type == EXP_CMD)
	// 	exp->process = &sh_expansions_command;
	// else if (exp->type == EXP_ARITH)
	// 	exp->process = &sh_expansions_arithmetic;
	else if (exp->type == EXP_TILDE)
		exp->process = &sh_expansions_tilde;
	else
		return (FAILURE);
	return (SUCCESS);
	(void)exp;
}
