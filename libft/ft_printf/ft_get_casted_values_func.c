/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values_func.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 22:33:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:04:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gtvar_long_long_int(t_pf *pf, va_list va)
{
	pf->var.integer = (long long int)va_arg(va, INTMAX);
}

void	ft_gtvar_intmax_t(t_pf *pf, va_list va)
{
	pf->var.integer = (INTMAX)va_arg(va, INTMAX);
}

void	ft_gtvar_uint(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned int)va_arg(va, INTMAX);
}

void	ft_gtvar_uchar(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned char)va_arg(va, INTMAX);
}

void	ft_gtvar_ulint(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned long int)va_arg(va, INTMAX);
}
