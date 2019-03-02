/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:47:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/02 14:56:50 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			ft_isseparator(char c)
{
	if (c == '<' || c == '>' || c == ';' || c == '|' || c == '\0')
		return (1);
	return (ft_iswhite(c));
}

int			sh_lexer(char *input)
{
	int			i;
	int			start;
	int			token;
	t_automate	automates[SH_LEXER_AUTO_LEN];

	i = 0;
	start = 0;
	sh_lexer_automate_init(automates);
//	sh_lexer_automate_show_status(automates, ' ');
	while (input[start])
	{
		i = start;
		while (input[i])
		{
			sh_lexer_automate_run(automates, input[i]);
			if ((token = sh_lexer_automate_check(automates)) != UNKNOWN)
			{
				sh_lexer_show_token(token);
				ft_putstrn(ft_strsub(input, start, i - start));
				ft_putnbrn(start);
				sh_lexer_automate_init(automates);
				break ;
			}
			i++;
		}
		while (ft_iswhite(input[i]))
			i++;
//		sh_lexer_automate_show_status(automates, input[i]);
		start = i;
//		if (input[start])
//			start++;
			
//		if (ft_iswhite(input[i]))
//			start = i + 1;
	}
	sh_lexer_automate_run(automates, input[i]);
//	sh_lexer_automate_show_status(automates, input[i]);
	if ((token = sh_lexer_automate_check(automates)) != UNKNOWN)
		sh_lexer_show_token(token);
	return (UNKNOWN);
}

























/*
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
*/