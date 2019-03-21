/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:00:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/21 12:34:03 by jmartel          ###   ########.fr       */
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
	ft_printf("processing : \n\texpansion : %s\n", expansion->expansion);
	if (!(expansion->res = ft_dystr_new(expansion->expansion, ft_strlen(expansion->expansion), ft_strlen(expansion->expansion))))
		return (LEX_EXP_ERR);
	ft_printf("processing : \n\texpansion : %s\n\tres : %s\n", expansion->expansion, expansion->res->str);
	expansion->res->size = ft_strlen(expansion->res->str);
	expansion->res->len = expansion->res->size;
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

