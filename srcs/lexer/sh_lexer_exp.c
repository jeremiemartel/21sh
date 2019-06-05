/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:54:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/05 13:11:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp(t_lexer *lexer)
{
	char	*start;
	char	*end;
	char	*original;

	original = lexer->input + lexer->tok_start + lexer->tok_len;
	if (!(start = ft_strpbrk(original, "$~`")))
		return (LEX_ERR);
	if (*start == '`')
		end = ft_strchr(start + 1, '`');
	else if (ft_strnstr(start, "$((", 3))
		end = ft_strstr(start, "))");
	else if (ft_strnstr(start, "$(", 2))
		end = ft_strstr(start, ")");
	else if (ft_strnstr(start, "${", 2))
		end = ft_strstr(start, "}");
	else if (ft_strnstr(start, "$", 1))
		(end = ft_strpbrk(start, " \t\n")) || (end = ft_strchr(start, '\0'));
	else if (ft_strnstr(start, "~", 1))
		(end = ft_strpbrk(start, " \t\n")) || (end = ft_strchr(start, '\0'));
	else
		end = NULL;
	if (!end)
		// Call quote funtion !
		return (ft_perror("Expansion", "Wrong Format"));
	lexer->tok_len += end - start;
	return (LEX_OK);
}
