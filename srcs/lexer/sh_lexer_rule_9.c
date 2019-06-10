/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:45:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 14:46:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule9(t_lexer *lexer)
{
	char	*start;

	if (lexer->c == '#')
	{
		start = lexer->input + lexer->tok_start;
		if (!ft_strchr(start, '\n'))
			lexer->input[lexer->tok_start] = 0;
		else
			ft_strcpy(start, ft_strchr(start, '\n'));
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
