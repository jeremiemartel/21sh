/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:48:50 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/11 19:47:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*res;

	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len] != 0)
		len++;
	if (!(res = (char*)malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	len = 0;
	while (s1[len])
	{
		res[len] = s1[len];
		len++;
	}
	res[len] = 0;
	return (res);
}
