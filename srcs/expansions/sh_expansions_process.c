/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/05 13:53:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_expansions_variable(t_context *context, t_expansion *exp)
{
	char	*value;

	if (*exp->expansion == '#')
		value = sh_vars_get_value(context->env, context->vars, exp->expansion + 1);
	else
		value = sh_vars_get_value(context->env, context->vars, exp->expansion);
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
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_variable (1)"));
	return (SUCCESS);
}

// int		sh_expansions_command(t_context *context, t_expansion *exp)
// {
// 	if (!(exp->res = ft_dy_str_new_str("")))
// 		return (FAILURE);
// 	return (SUCCESS);
// 	(void)lexer;
// 	(void)exp;
// }

// int		sh_expansions_arithmetic(t_context *context, t_expansion *exp)
// {
// 	if (!(exp->res = ft_dy_str_new_str("")))
// 		return (FAILURE);
// 	return (SUCCESS);
// 	(void)lexer;
// 	(void)exp;
// }
