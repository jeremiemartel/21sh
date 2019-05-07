/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:54:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/07 14:54:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp(t_lexer *lexer)
{
	sh_lexer_exp_recursive(lexer, &lexer->input, lexer->input);
	return (LEX_ERR);
}

int		sh_lexer_exp_recursive(t_lexer *lexer, char **input, char *original)
{
	t_expansion	exp;

	sh_lexer_exp_init(original, &exp);
	t_expansion_show(&exp);
	// if (sh_lexer_exp_detect_expansion(exp))
	// {
	// 	sh_lexer_exp_recursive(lexer, input, exp.expansion);
		// update expansion !
		// t_expansion_update(original, &exp);
	// }
	// exp.process(lexer, &exp);
	return (LEX_OK);
	(void)input;
	(void)lexer;
}

/*
int		t_expansion_init_process(t_expansion *exp)
{
	if (exp->type == 1)
		exp->process = &sh_lexer_exp_variable;
	else if (exp->type == 2)
		exp->process = &sh_lexer_exp_parameter;
	else if (exp->type == 3)
		exp->process = &sh_lexer_exp_command;
	else if (exp->type == 4)
		exp->process = &sh_lexer_exp_arithmetic;
	else if (exp->type == 5)
		exp->process = &sh_lexer_exp_tilde;
	else
		return (LEX_ERR);
	return (LEX_OK);
}
*/
int		sh_lexer_exp_init(char *original, t_expansion *exp)
{
	char	*start;

	exp->res = NULL;
	if (!(start = ft_strpbrk(original, "$~`")))
		return (LEX_ERR);
	if (*start == '`')
		sh_exp_detect_original_pattern(exp, start, "`", LEX_EXP_CMD);
	else if (ft_strnstr(start, "$((", 3))
		sh_exp_detect_original_pattern(exp, start, "))", LEX_EXP_ARITH);
	else if (ft_strnstr(start, "$(", 2))
		sh_exp_detect_original_pattern(exp, start, ")", LEX_EXP_CMD);
	else if (ft_strnstr(start, "${", 2))
		sh_exp_detect_original_pattern(exp, start, "}", LEX_EXP_PARAM);
	else if (ft_strnstr(start, "$", 1))
		sh_exp_detect_original_chars(exp, start, " \t\n\0", LEX_EXP_VAR);
	else if (ft_strnstr(start, "~", 1))
		sh_exp_detect_original_chars(exp, start, "/ \t\n\0", LEX_EXP_TILDE);
	else
		return (LEX_ERR);
	return (LEX_OK);
}

int			sh_exp_detect_original_pattern(t_expansion *exp, char *start, char *pattern, int type)
{
	char	*end;

	exp->type = type;
	if (!(end = ft_strstr(start, pattern)))
		return (LEX_ERR);
	end += ft_strlen(pattern);
	if (!(exp->original = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_detect_original_pattern (1)"));
	if (*start == '$' && (start[1] == '(' || start[1] == '{'))
	{
		start += 2;
		if (*start == '(')
			start++;
	}
	else
		start++;
	if (!(exp->expansion = ft_strndup(start, end -ft_strlen(pattern) - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_detect_original_pattern (2)"));
	return (LEX_OK);
}

int			sh_exp_detect_original_chars(t_expansion *exp, char *start, char *pattern, int type)
{
	char	*end;

	exp->type = type;
	if (!(end = ft_strstr(start, pattern)))
		return (LEX_ERR);
	end += ft_strlen(pattern);
	if (!(exp->original = ft_strndup(start, end - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_detect_original_pattern"));
	if (*start == '$' && (start[1] == '(' || start[1] == '{'))
	{
		start += 2;
		if (*start == '(')
			start++;
	}
	else
		start++;
	if (!(exp->expansion = ft_strndup(start, end -ft_strlen(pattern) - start)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_detect_original_pattern"));
	return (LEX_OK);
}
