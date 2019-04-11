/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:00:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/22 13:48:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_process(t_lexer *lexer, t_expansion *expansion)
{
	if (expansion->type == LEX_EXP_CMD)
		return (lexer_expansion_process_command(lexer, expansion));
	else if (expansion->type == LEX_EXP_ARITH)
		return (lexer_expansion_process_arithmetic(lexer, expansion));
	else if (expansion->type == LEX_EXP_PARAM)
		return (lexer_expansion_process_parameter(lexer, expansion));
	else if (expansion->type == LEX_EXP_VAR)
		return (lexer_expansion_process_variable(lexer, expansion));
	return (LEX_EXP_ERR);
}

int			lexer_expansion_process_command(t_lexer *lexer, t_expansion *expansion)
{
	if (!(expansion->res = ft_dystr_new(expansion->expansion, ft_strlen(expansion->expansion), ft_strlen(expansion->expansion))))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
	(void)lexer;
	(void)expansion;
}

int			lexer_expansion_process_arithmetic(t_lexer *lexer, t_expansion *expansion)
{
	if (!(expansion->res = ft_dystr_new(expansion->expansion, ft_strlen(expansion->expansion), ft_strlen(expansion->expansion))))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
	(void)lexer;
	(void)expansion;
}

int			lexer_expansion_process_parameter(t_lexer *lexer, t_expansion *expansion)
{
	if (!(expansion->res = ft_dystr_new(expansion->expansion, ft_strlen(expansion->expansion), ft_strlen(expansion->expansion))))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
	(void)lexer;
	(void)expansion;
}

int			lexer_expansion_process_variable(t_lexer *lexer, t_expansion *expansion)
{
	if (!(expansion->res = ft_dystr_new("", 0, 0)))
		return (LEX_EXP_ERR);
	return (LEX_EXP_ERR);
	(void)lexer;
	(void)expansion;
}
