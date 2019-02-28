/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:47:30 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/09 17:47:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	len;
	char			*res;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (!(res = (char*)malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	res[len] = 0;
	len = 0;
	while (s[len])
	{
		res[len] = f(s[len]);
		len++;
	}
	return (res);
}
