/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:25:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 22:42:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule2(t_lexer *lexer)
{
	static char	operators[] = "|&;<>()";

	if (lexer->quoted > 0 || lexer->current_id == LEX_TOK_UNKNOWN)
		return (LEX_CONTINUE);
	if (!ft_strchr(operators, lexer->current_id & 0x00ff))
		return (LEX_CONTINUE);
	if (ft_strchr(operators, lexer->c) || lexer->c == '-')
	{
		if (!(lexer->current_id & 0xff00))
		{
			if (sh_lexer_is_operator(lexer->current_id + 0xff00 * lexer->c))
				lexer->current_id += 0xff00 * lexer->c;
			else
				return (LEX_CONTINUE);
		}
		else if (lexer->c == '-' && lexer->current_id == '<' + '<' * 0xff00)
			lexer->current_id += 0xff0000 * lexer->c;
		else
			return (LEX_CONTINUE);
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
