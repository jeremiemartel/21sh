/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/11 13:41:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp_variable(t_lexer *lexer, t_expansion *exp)
{
	char	*value;

	if (*exp->expansion == '#')
		value = sh_vars_get_value(lexer->env, lexer->vars, exp->expansion + 1);
	else
		value = sh_vars_get_value(lexer->env, lexer->vars, exp->expansion);
	if (*exp->expansion == '#')
	{
		if (!value)
			exp->res = ft_dy_str_new_str("0");
		else
			exp->res = ft_dy_str_new_ptr(ft_itoa(ft_strlen(value)));
	}
	else
	{
		if (!value)
			exp->res = ft_dy_str_new_str("");
		else
			exp->res = ft_dy_str_new_str(value);
	}
	if (!(exp->res))
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_variable (1)"));
	return (LEX_OK);
}

int		sh_lexer_exp_command(t_lexer *lexer, t_expansion *exp)
{
	if (!(exp->res = ft_dy_str_new_str("")))
		return (LEX_ERR);
	return (LEX_OK);
	(void)lexer;
	(void)exp;
}

int		sh_lexer_exp_arithmetic(t_lexer *lexer, t_expansion *exp)
{
	if (!(exp->res = ft_dy_str_new_str("")))
		return (LEX_ERR);
	return (LEX_OK);
	(void)lexer;
	(void)exp;
}
