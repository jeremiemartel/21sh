/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:33:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/31 17:13:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_sym(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	itoa_len(int n)
{
	int len;

	len = 0;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len + 1);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(res = (char*)malloc(sizeof(*res) * (itoa_len(n) + itoa_sym(n) + 1))))
		return (NULL);
	i = itoa_len(n) + itoa_sym(n);
	res[i--] = 0;
	if (n < 0)
	{
		res[0] = '-';
		n = -1 * n;
	}
	while (n / 10 != 0)
	{
		res[i--] = n % 10 + '0';
		n = n / 10;
	}
	res[i] = n % 10 + '0';
	return (res);
}
