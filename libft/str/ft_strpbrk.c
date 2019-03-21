/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:27:52 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/21 16:39:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strpbrk:
**		Locates  in s the first occurence of any char in charset
**	Return Value:
**		Pointer to the character found if any
**		NULL else
*/

char		*strpbrk(const char *s, const char *charset)
{
	int		i;
	int		j;

	if (!s || !*s|| !charset || !*charset)
		return (NULL);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
		{
			if (s[i] == charset[j])
				return ((char*)s + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
