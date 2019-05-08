/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/08 13:53:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp_variable(t_lexer *lexer, t_expansion *exp)
{
	char	*value;

	value = sh_vars_get_value(lexer->vars, exp->expansion);
	if (!value)
		exp->res = ft_dy_str_new_from("");
	else
		exp->res = ft_dy_str_new_from(value);
	if (!(exp->res))
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_varriable (1)"));
	return (LEX_OK);
}

int		sh_lexer_exp_parameter(t_lexer *lexer, t_expansion *exp)
{
	if (!(exp->res = ft_dy_str_new_from("")))
		return (LEX_ERR);
	return (LEX_OK);
	(void)lexer;
	(void)exp;
}

int		sh_lexer_exp_command(t_lexer *lexer, t_expansion *exp)
{
	if (!(exp->res = ft_dy_str_new_from("")))
		return (LEX_ERR);
	return (LEX_OK);
	(void)lexer;
	(void)exp;
}

int		sh_lexer_exp_arithmetic(t_lexer *lexer, t_expansion *exp)
{
	if (!(exp->res = ft_dy_str_new_from("")))
		return (LEX_ERR);
	return (LEX_OK);
	(void)lexer;
	(void)exp;
}
