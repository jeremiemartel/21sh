/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_automates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:21:37 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/04 18:10:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_lexer_auto_while(int status, char c)
{
	char	pattern[] = "while";
	int		len = 5;

	if (status == error || status == end)
		return (error);
	if (status == len)
	{
		if (ft_isseparator(c))
			return (end);
		return (error);
	}
	if (pattern[status] == c)
		return (status + 1);
	if (ft_iswhite(c))
		return (0);
	return (error);
}

int			sh_lexer_auto_less(int status, char c)
{
	char	pattern[] = "<";
	int		len = 1;

	if (status == error || status == end)
		return (error);
	if (c != *pattern && ft_isseparator(c))
		return (0);
	if (pattern[status] == c)
	{
		if (status == len - 1)
			return (end);
		return (status + 1);
	}
	return (error);
}

int			sh_lexer_auto_great(int status, char c)
{
	char	pattern[] = ">";
	int		len = 1;

	if (status == error || status == end)
		return (error);
	if (c != *pattern && ft_isseparator(c))
		return (0);
	if (pattern[status] == c)
	{
		if (status == len - 1)
			return (end);
		return (status + 1);
	}
	return (error);
}

int			sh_lexer_auto_word(int status, char c)
{
	if (status == error)
		return (error);
	if (ft_iswhite(c))
	{
		if (status > 0)
			return (end);
		return (error);
	}
	if (ft_isseparator(c))
	{
//		if (status > 0)
//			return (end);
		return (end);
	}
	return (status + 1);
}

int			sh_lexer_auto_space(int status, char c)
{
	if (status == error)
		return (error);
	if (ft_iswhite(c))
		return (end);
	return (error);
}
