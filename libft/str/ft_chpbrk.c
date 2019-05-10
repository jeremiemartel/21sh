/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chpbrk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:40:42 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/09 12:57:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_chpbrk:
**		Say if char c is one the characters given in charset
**	Return Value:
**		2 : if c is '\0'
**		1 : if true
**		0 : if false
*/

int			ft_chpbrk(const char c, const char *charset)
{
	int		i;

	if (!c)
		return (2);
	if (!charset || !*charset)
		return (0);
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
