/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:00:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 19:20:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_process(t_lexer *lexer, t_expansion *expansion)
{
	if (expansion->type == LEX_EXP_CMD)
		lexer_expansion_process_command(lexer, expansion);
	else if (expansion->type == LEX_EXP_ARITH)
		lexer_expansion_process_arithmetic(lexer, expansion);
	else if (expansion->type == LEX_EXP_PARAM)
		lexer_expansion_process_parameter(lexer, expansion);
	else if (expansion->type == LEX_EXP_VAR)
		lexer_expansion_process_variable(lexer, expansion);
	return (LEX_EXP_OK);
}

int			lexer_expansion_process_command(t_lexer *lexer, t_expansion *expansion)
{
	ft_putstrn("process command : Check 0");
	if (!(expansion->res))////
		if (!(expansion->res = ft_dystr_new("Command res", 11, 11)))
			return (LEX_EXP_ERR);
	ft_putstrn("process command : Check 1");
	expansion->res->size = ft_strlen(expansion->res->str);
	ft_putstrn("process command : Check 2");
	expansion->res->len = expansion->res->size;
	ft_putstrn("process command : Check 3");
	return (LEX_EXP_OK);
	(void)lexer;
	(void)expansion;
}
int			lexer_expansion_process_arithmetic(t_lexer *lexer, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)lexer;
	(void)expansion;
}
int			lexer_expansion_process_parameter(t_lexer *lexer, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)lexer;
	(void)expansion;
}
int			lexer_expansion_process_variable(t_lexer *lexer, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)lexer;
	(void)expansion;
}

