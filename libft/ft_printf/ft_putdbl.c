/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:56:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:04:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putdbl_process(int d, int decal, t_pf *pf)
{
	if (d / 10 == 0)
	{
		ft_putchar_buff(d % 10 + '0', pf);
	}
	else
	{
		ft_putdbl_process(d / 10, decal - 1, pf);
		ft_putchar_buff(d % 10 + '0', pf);
	}
	if (decal == 0)
		ft_putchar_buff('.', pf);
}

void	ft_putdbl_short(double d, int precision, t_pf *pf)
{
	int		decal;
	double	frac;

	decal = 0;
	frac = d - (int)d;
	while (frac != 0 && precision)
	{
		d = d * 10;
		frac = d - (int)d;
		decal++;
		precision--;
	}
	if (d < 0)
		ft_putchar_buff('-', pf);
	ft_putdbl_process(ft_fabs(d), decal, pf);
	precision--;
	while (precision >= 0)
	{
		ft_putchar_buff('0', pf);
		precision--;
	}
}

void	ft_process_precision_double(int pre, double frac, int decal, t_pf *pf)
{
	double frac2;

	frac2 = 1;
	while (frac2 != 0 && pre)
	{
		frac = frac * 10;
		frac2 = frac - (INTMAX)frac;
		decal++;
		pre--;
	}
	ft_putchar_buff('.', pf);
	ft_putnbr_max((INTMAX)frac, pf);
	pre--;
	while (pre >= 0)
	{
		ft_putchar_buff('0', pf);
		pre--;
	}
}

void	ft_putdbl_long(double d, int precision, t_pf *pf)
{
	int		decal;
	double	frac;

	if (d < 0)
	{
		ft_putchar_buff('-', pf);
		d = -d;
	}
	decal = 0;
	frac = d - (INTMAX)d;
	ft_putnbr_max(ft_abs_max((INTMAX)(d)), pf);
	if (precision != 0)
		ft_process_precision_double(precision, frac, decal, pf);
}

void	ft_putdbl(double d, int precision, t_pf *pf)
{
	if (ft_fabs(d) > 65655)
		ft_putdbl_long(d, precision, pf);
	else
		ft_putdbl_short(d, precision, pf);
}
