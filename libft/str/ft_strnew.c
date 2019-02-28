/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:42:57 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/09 16:42:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*res;
	size_t	i;

	if (!(res = (char*)malloc(sizeof(*res) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = 0;
		i++;
	}
	res[i] = 0;
	return (res);
}
