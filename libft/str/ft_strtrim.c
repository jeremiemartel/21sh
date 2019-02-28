/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:34:27 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/09 19:34:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istrim(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	else
		return (0);
}

static char	*ft_trim(char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_istrim(s[i]))
		i++;
	if (i > 0)
		s[i - 1] = 0;
	return (s + i);
}

char		*ft_strtrim(char const *s)
{
	char	*buf;
	char	*res;

	if (s == NULL)
		return (NULL);
	buf = ft_strdup(s);
	if (!buf)
		return (NULL);
	buf = ft_trim(buf);
	ft_strrev(buf);
	buf = ft_trim(buf);
	ft_strrev(buf);
	res = ft_strdup(buf);
	return (res);
}
