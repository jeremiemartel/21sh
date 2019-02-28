/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:39:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:39:40 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbrlen(unsigned long long l, unsigned long long lbase)
{
	int		nb;

	nb = 0;
	while (l > 0)
	{
		nb++;
		l = l / lbase;
	}
	return (nb);
}

static void		ft_ulltoa_rec(unsigned long long ul,
		unsigned long long lbase, char *str)
{
	if (ul < lbase)
	{
		if (ul % lbase < 10)
			str[0] = ul % lbase + '0';
		else
			str[0] = ul % lbase + 'A' - 10;
		return ;
	}
	else
	{
		ft_ulltoa_rec(ul / lbase, lbase, &str[1]);
		if (ul % lbase < 10)
			str[0] = ul % lbase + '0';
		else
			str[0] = ul % lbase + 'A' - 10;
	}
}

char			*ft_ulltoa(unsigned long long l, int base)
{
	char				*str;
	unsigned long long	lbase;
	int					len;

	if (l == 0)
		return (ft_strdup("0"));
	len = 0;
	lbase = (unsigned long long)base;
	len += ft_nbrlen(l, lbase);
	if (!(str = ft_strnew(sizeof(char) * len)))
		return (NULL);
	ft_ulltoa_rec(l, lbase, str);
	ft_strrev(str);
	return (str);
}
