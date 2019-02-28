/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:49:35 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/11 19:14:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (len == 0)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			*(unsigned char*)(dst + len - 1) = *(unsigned char*)(src + len - 1);
			len--;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
