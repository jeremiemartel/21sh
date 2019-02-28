/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fill2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:54:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:41:25 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** "Mothers functions", call all the subfunctions depending on type and flags
** Supported types in this file are : p, s, c, percent
*/

void		fill_p(va_list va, t_conv *conv)
{
	long long	nb;
	char		*buf;

	nb = va_arg(va, long long);
	buf = ft_lltoa(nb, 16);
	buf = ft_strtolower(buf);
	conv->res = ft_strjoin_free("0x", buf, 0);
	if (conv->size != NO_SIZE)
		flag_size_p(conv);
	free(buf);
}

void		fill_s(va_list va, t_conv *conv)
{
	conv->res = va_arg(va, char*);
	if (conv->res == NULL)
		conv->res = ft_strdup("(null)");
	else
		conv->res = ft_strdup(conv->res);
	if (conv->prec != NO_PREC)
		flag_prec_s(conv);
	if (conv->size != NO_SIZE)
		flag_size_s(conv);
}

void		fill_c(va_list va, t_conv *conv)
{
	char	buf;

	buf = (char)va_arg(va, int);
	conv->res = ft_strnew(2);
	conv->res[0] = buf;
	conv->res[1] = 0;
	if (conv->size != NO_SIZE)
		flag_size_c(conv);
}

void		fill_perc(t_conv *conv)
{
	conv->res = ft_strdup("%");
	if (conv->size != NO_SIZE)
		flag_size_perc(conv);
	return ;
}

void		fill_b(va_list va, t_conv *conv)
{
	unsigned long long		nb;

	nb = cast_u(va, conv);
	conv->res = ft_ulltoa(nb, 2);
	if (conv->prec != NO_PREC)
		flag_prec_o(conv);
	if (conv->size != NO_SIZE)
		flag_size_o(conv);
}
