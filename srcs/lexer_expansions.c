/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:40:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 07:08:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int         lexer_expansion(t_lexer *lexer)
{
    return (LEX_OK);
}

int         lexer_parameter_expansion(t_lexer *lexer)
{
    ft_putstrn("parameter expansion");
    return (LEX_ERR);
    (void)lexer;
}

int         lexer_arithmetic_expression(t_lexer *lexer)
{
    ft_putstrn("arithmetic expression");
    return (LEX_ERR);
    (void)lexer;
}

int         lexer_command_substitution(t_lexer *lexer)
{
    ft_putstrn("command substitution");
    return (LEX_ERR);
    (void)lexer;
}
