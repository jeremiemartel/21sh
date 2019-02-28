/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:40:43 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/08 10:40:44 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t lensrc;
	size_t lendst;

	i = 0;
	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (size <= lendst)
		return (lensrc + size);
	while (i < size - lendst - 1 && src[i])
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lensrc + lendst);
}
