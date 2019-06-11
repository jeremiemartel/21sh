/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:25:15 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule1(t_lexer *lexer)
{
	if (lexer->c == '\0')
	{
		if (lexer->quoted > 0)
		{
			if (!isatty(0))
			{
				sh_perror(SH_ERR1_UNEXPECTED_EOF, "sh_lexer_rule1");
				return (LEX_FAIL);
			}
			else
				return (sh_process_quoted(lexer));
		}
		sh_lexer_add_token(lexer);
		return (LEX_END);
	}
	return (LEX_CONTINUE);
}
