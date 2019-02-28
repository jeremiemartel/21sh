/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:39:33 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:39:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbrlen(unsigned long l, unsigned long lbase)
{
	int				nb;

	nb = 0;
	while (l > 0)
	{
		nb++;
		l = l / lbase;
	}
	return (nb);
}

static void		ft_ltoa_rec(unsigned long ul, unsigned long lbase, char *str)
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
		ft_ltoa_rec(ul / lbase, lbase, &str[1]);
		if (ul % lbase < 10)
			str[0] = ul % lbase + '0';
		else
			str[0] = ul % lbase + 'A' - 10;
	}
}

char			*ft_ltoa(long l, int base)
{
	char			*str;
	unsigned long	ul;
	unsigned long	lbase;
	int				neg;
	int				len;

	if (l == 0)
		return (ft_strdup("0"));
	neg = 1;
	len = 0;
	if (l < 0 && base == 10)
	{
		neg = -1;
		len = 1;
	}
	ul = neg * l;
	lbase = (long)base;
	len += ft_nbrlen(ul, lbase);
	if (!(str = ft_strnew(sizeof(char) * len)))
		return (NULL);
	ft_ltoa_rec(ul, lbase, str);
	if (neg == -1)
		ft_strcat(str, "-");
	ft_strrev(str);
	return (str);
}
