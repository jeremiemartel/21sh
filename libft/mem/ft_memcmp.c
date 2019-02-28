/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:38:32 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/09 11:38:34 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1)
	{
		if (*(unsigned char*)(s1 + i) != *(unsigned char*)(s2 + i))
			break ;
		i++;
	}
	return (*(unsigned char*)(s1 + i) - *(unsigned char*)(s2 + i));
}
