/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/08 12:34:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp_variable(t_lexer *lexer, t_expansion *exp)
{
	if (!(exp->res = ft_dy_str_new_from("")))
		return (LEX_ERR);
	return (LEX_OK);
	(void)lexer;
	(void)exp;
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
