/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 20:27:00 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/09 20:27:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	splitlen(char const *s, char c)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (len);
}

static char	*splitdup(char const *s, char c)
{
	int		len;
	char	*res;

	if (s == NULL)
		return (NULL);
	while (*s && *s == c)
		s++;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (!(res = (char*)malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		res[len] = s[len];
		len++;
	}
	res[len] = 0;
	return (res);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	if (!(res = (char**)malloc(sizeof(*res) * (splitlen(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			res[j++] = splitdup(s + i, c);
		while (s[i] && s[i] != c)
			i++;
	}
	res[j] = NULL;
	return (res);
}
