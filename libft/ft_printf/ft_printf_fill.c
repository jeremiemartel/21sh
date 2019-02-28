/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:26:52 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:36:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** "Mothers functions", call the subfunctions depending on type and flags
** Supported types in this file are : di, x, o, u, f
*/

void		fill_di(va_list va, t_conv *conv)
{
	int			sign;

	cast_di(va, conv);
	sign = (*conv->res == '-') ? -1 : 1;
	if (conv->conv & FLAG_PLUS)
		flag_plus(conv, sign);
	else if (conv->conv & FLAG_SPACE)
		flag_space(conv, sign);
	if (conv->prec == 0 && ft_strequ(conv->res, "0"))
		conv->res[0] = 0;
	if (conv->prec == 0 && ft_strequ(conv->res, "+0"))
		conv->res[1] = 0;
	if (conv->prec != NO_PREC)
		flag_prec_di(conv);
	if (conv->size != NO_SIZE)
		flag_size_di(conv);
	return ;
}

void		fill_x(va_list va, t_conv *conv)
{
	long long	nb;

	nb = cast_xo(va, conv);
	conv->res = ft_lltoa(nb, 16);
	if (nb == 0)
		conv->conv = conv->conv & ~FLAG_HASH;
	if (conv->type == 'x')
		conv->res = ft_strtolower(conv->res);
	if ((conv->conv & FLAG_HASH) && nb != 0)
		flag_hash_x(conv);
	if (conv->prec == 0 && ft_strequ(conv->res, "0"))
		conv->res[0] = 0;
	if (conv->prec != NO_PREC)
		flag_prec_x(conv);
	if (conv->size != NO_SIZE)
		flag_size_x(conv);
	return ;
}

void		fill_o(va_list va, t_conv *conv)
{
	long long	nb;

	nb = cast_xo(va, conv);
	conv->res = ft_lltoa(nb, 8);
	if ((conv->conv & FLAG_HASH) && nb != 0)
		flag_hash_o(conv);
	if (conv->prec == 0 && ft_strequ(conv->res, "0"))
		conv->res[0] = 0;
	if (conv->prec != NO_PREC)
		flag_prec_o(conv);
	if (conv->size != NO_SIZE)
		flag_size_o(conv);
}

void		fill_u(va_list va, t_conv *conv)
{
	unsigned long long	nb;

	nb = cast_u(va, conv);
	conv->res = ft_ulltoa(nb, 10);
	if (conv->prec == 0 && ft_strequ(conv->res, "0"))
		conv->res[0] = 0;
	if (conv->prec != NO_PREC)
		flag_prec_u(conv);
	if (conv->size != NO_SIZE)
		flag_size_u(conv);
}

void		fill_f(va_list va, t_conv *conv)
{
	int				sign;

	if (conv->prec == NO_PREC)
		conv->prec = 6;
	cast_f(va, conv);
	sign = (*conv->res == '-') ? -1 : 1;
	if (conv->conv & FLAG_PLUS)
		flag_plus(conv, sign);
	else if (conv->conv & FLAG_SPACE)
		flag_space(conv, sign);
	if (conv->conv & FLAG_HASH)
		flag_hash_f(conv);
	if (conv->size != NO_SIZE)
		flag_size_f(conv);
}
