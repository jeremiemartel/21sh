/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:27:52 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 22:46:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strpbrk:
**		Locates  in string s the first occurence of any char in charset
**	Returned Values:
**		NULL : any character found
**		Else : Pointer to the character found if any
*/

char		*ft_strpbrk(const char *s, const char *charset)
{
	int		i;
	int		j;

	if (!s || !*s || !charset || !*charset)
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
