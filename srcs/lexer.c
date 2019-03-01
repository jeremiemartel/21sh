/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:47:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/01 18:11:42 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define SH_LEX_NO	-1
#define SH_LEX_YES	-2

int			sh_lexer_is_reserved(char c)
{
	if (c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

int			sh_lexer_is_separator(char c)
{
	if (ft_iswhite(c))
		return (1);
	if (c == '\0' || c == ';')
		return (1);
	return (0);
}

int			sh_lexer_automate_redirection(char *buffer)
{
	int		i;

	i = 0;
	if (ft_strstr(buffer, "<<"))
	if (ft_strchr(buffer, '<') || ft_strchr(buffer, '>'))
		return (IO_NUMBER);
	return (SH_LEX_NO);
}

int			sh_lexer_automate_word(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (sh_lexer_is_reserved(buffer[i]))
			return (SH_LEX_NO);
		i++;		
	}
	return (WORD);
}

int			sh_lexer(char *input)
{
	int		i;
	int		ib;
	char	buffer[128];

	i = 0;
	while (input[i])
	{
		ib = 0;
		while (!sh_lexer_is_separator(input[i]))
		{
			buffer[ib] = input[i];
			i++;
		}
		if (sh_lexer_automate_word(buffer) == WORD)
			ft_putstr("WORD ");
		if (sh_lexer_automate_redirection(buffer) == IO_NUMBER)
			ft_putstr("REDIR ");
		ft_putstrn("");
		while (input[i] && sh_lexer_is_separator(input[i]))
			i++;
	}
	return (1);
}
