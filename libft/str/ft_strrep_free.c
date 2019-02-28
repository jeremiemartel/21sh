/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 09:31:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/02/27 09:24:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strrep_free : look for pattern in s1, and replace it by s2
**		It allocate a new string, do you can use param to free any arguments
**		param:
**			if param & 0x0001 : free s1
**			if param & 0x0002 : free s2
**			if param & 0x0004 : free pattern
**		return:
**			NULL : if any error occur (can't find pattern, can't allocate mem)
**			address of new string else
*/

static void	ft_strrep_free_free(char *s1, char *s2, char *pattern, int param)
{
	if (param & 0x0001)
		free(s1);
	if (param & 0x0002)
		free(s2);
	if (param & 0x0004)
		free(pattern);
}

char		*ft_strrep_free(char *s1, char *s2, char *pattern, int param)
{
	char	*res;
	int		i1;
	int		i2;
	int		lenp;
	char	*pt;

	if (!(pt = ft_strstr(s1, pattern)))
		return (NULL);
	lenp = (ft_strlen(s1) + ft_strlen(s2) - ft_strlen(pattern) + 1);
	if (!(res = malloc(sizeof(*res) * lenp)))
		return (NULL);
	i1 = -1;
	while (s1 + ++i1 != pt)
		res[i1] = s1[i1];
	i2 = -1;
	while (s2[++i2])
		res[i1 + i2] = s2[i2];
	lenp = ft_strlen(pattern);
	i1--;
	while (s1[++i1 + lenp])
		res[i1 + i2] = s1[i1 + lenp];
	res[i1 + i2] = 0;
	ft_strrep_free_free(s1, s2, pattern, param);
	return (res);
}
