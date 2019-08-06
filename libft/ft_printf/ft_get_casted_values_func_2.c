/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values_func_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 22:33:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:04:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gtvar_none(t_pf *pf, va_list va)
{
	pf->var.integer = (int)va_arg(va, INTMAX);
}

void	ft_gtvar_signed_char(t_pf *pf, va_list va)
{
	pf->var.integer = (signed char)va_arg(va, INTMAX);
}

void	ft_gtvar_short_int(t_pf *pf, va_list va)
{
	pf->var.integer = (short)va_arg(va, INTMAX);
}

void	ft_gtvar_size_t(t_pf *pf, va_list va)
{
	pf->var.integer = (size_t)va_arg(va, INTMAX);
}

void	ft_gtvar_long_int(t_pf *pf, va_list va)
{
	pf->var.integer = (long int)va_arg(va, INTMAX);
}
