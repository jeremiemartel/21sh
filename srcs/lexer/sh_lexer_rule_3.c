/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:33:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/07 09:38:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule3(t_lexer *lexer)
{
	char		operators[LEX_OPERATORS_CHARS_LEN];

	ft_strcpy(operators, LEX_OPERATORS_CHARS);
	if (!lexer->current_id)
		return (LEX_CONTINUE);
	if (!(ft_strchr(operators, lexer->current_id & 0x00ff)))
		return (LEX_CONTINUE);
	if (!ft_strchr(operators, lexer->c))
	{
		if (sh_lexer_is_operator(lexer->current_id))
		{
			t_lexer_add_token(lexer);
			lexer->tok_len = 0;
			return (LEX_OK);
		}
		return (LEX_ERR);
	}
	return (LEX_CONTINUE);
}
