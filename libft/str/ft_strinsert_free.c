/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:06:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/10 09:33:16 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert s2 at position pos in s1
** Returns a brand new char*, so you can chosse to free s1 and/or s2 with param
** param = 1 : free s1, param = 2 : free s2, param = 3 : free both
*/

static void		ft_strinsert_free_free(char *s1, char *s2, int param)
{
	if (param == 1 || param == 3)
		free(s1);
	if (param == 2 || param == 3)
		free(s2);
}

char			*ft_strinsert_free(char *s1, char *s2, int pos, int param)
{
	int		len1;
	int		len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (pos > len1)
		return (NULL);
	if ((res = (char*)malloc(sizeof(*res) * (len1 + len2 + 1))))
	{
		len1 = -1;
		while (++len1 < pos)
			res[len1] = s1[len1];
		len2 = -1;
		while (s2[++len2])
			res[len1 + len2] = s2[len2];
		while (s1[len1])
		{
			res[len1 + len2] = s1[len1];
			len1++;
		}
		res[len1 + len2] = 0;
	}
	ft_strinsert_free_free(s1, s2, param);
	return (res);
}
