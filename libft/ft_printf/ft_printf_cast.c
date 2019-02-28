/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:50:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:28:40 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Functions used to take args from va_list
** It depends on type and l, ll, h, hh flags
*/

void				cast_di(va_list va, t_conv *conv)
{
	if (conv->conv & CAST_H)
		conv->res = ft_itoa((short)va_arg(va, int));
	else if (conv->conv & CAST_HH)
		conv->res = ft_itoa((char)va_arg(va, int));
	else if (conv->conv & CAST_L)
		conv->res = ft_ltoa(va_arg(va, long), 10);
	else if (conv->conv & CAST_LL)
		conv->res = ft_lltoa(va_arg(va, long long), 10);
	else
		conv->res = ft_itoa((int)va_arg(va, int));
}

unsigned long long	cast_xo(va_list va, t_conv *conv)
{
	long long	nb;

	if ((conv->conv & CAST_H) != 0)
		nb = (unsigned short)va_arg(va, unsigned int);
	else if ((conv->conv & CAST_HH) != 0)
		nb = (unsigned char)va_arg(va, unsigned int);
	else if ((conv->conv & CAST_L) != 0)
		nb = va_arg(va, unsigned long);
	else if ((conv->conv & CAST_LL) != 0)
		nb = va_arg(va, unsigned long long);
	else
		nb = va_arg(va, unsigned int);
	return (nb);
}

unsigned long long	cast_u(va_list va, t_conv *conv)
{
	unsigned long long	nb;

	if ((conv->conv & CAST_H) != 0)
		nb = (unsigned short)va_arg(va, unsigned int);
	else if ((conv->conv & CAST_HH) != 0)
		nb = (unsigned char)va_arg(va, unsigned int);
	else if ((conv->conv & CAST_L) != 0)
		nb = va_arg(va, unsigned long);
	else if ((conv->conv & CAST_LL) != 0)
		nb = va_arg(va, unsigned long long);
	else
		nb = va_arg(va, unsigned int);
	return (nb);
}

void				cast_f(va_list va, t_conv *conv)
{
	if ((conv->conv & CAST_L) != 0)
		conv->res = ft_ftoa(va_arg(va, double), conv->prec);
	else if ((conv->conv & CAST_LL) != 0)
		conv->res = ft_ftoa(va_arg(va, long double), conv->prec);
	else
		conv->res = ft_ftoa(va_arg(va, double), conv->prec);
}
