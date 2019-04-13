/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion_process_tilde.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:43:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/11 17:51:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_process_tilde(t_lexer *lexer, t_expansion *expansion)
{
	if (!(expansion->res = ft_dystr_new("tildeExp", 15, 15)))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
	(void)lexer;
	(void)expansion;
}
