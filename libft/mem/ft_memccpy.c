/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:18:24 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/09 12:18:25 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	int n;

	n = len;
	if (n == 0)
		return (NULL);
	while (*(unsigned char*)(src) != (unsigned char)c && n > 0)
	{
		*(char*)(dst) = *(char*)(src);
		dst++;
		src++;
		n--;
	}
	if (*(unsigned char*)(src) == (unsigned char)c && n >= 1)
	{
		*(char*)(dst) = *(char*)(src);
		return (dst + 1);
	}
	else
		return (NULL);
}
