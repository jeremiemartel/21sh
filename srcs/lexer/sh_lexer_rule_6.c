/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:43:21 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 14:55:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_lexer_rule6_detect_io_number(t_lexer *lexer)
{
	char	*str;
	int		len;
	int		i;

	str = lexer->input + lexer->tok_start;
	len = lexer->tok_len;
	i = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			sh_lexer_rule6(t_lexer *lexer)
{
	static char		operators[] = "|&;<>()";

	if (lexer->quoted > 0)
		return (LEX_CONTINUE);
	if (ft_strchr(operators, lexer->c))
	{
		if (lexer->current_id == LEX_TOK_WORD)
			if (sh_lexer_rule6_detect_io_number(lexer))
				lexer->current_id = LEX_TOK_IO_NUMBER;
		sh_lexer_add_token(lexer);
		lexer->tok_len = 1;
		lexer->current_id = lexer->c & 0x00ff;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
