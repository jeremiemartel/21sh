/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_casted_values_func_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 22:33:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:04:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gtvar_ullint(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned long long int)va_arg(va, INTMAX);
}

void	ft_gtvar_uintmax_t(t_pf *pf, va_list va)
{
	pf->var.integer = (UINTMAX)va_arg(va, INTMAX);
}

void	ft_gtvar_ushort_int(t_pf *pf, va_list va)
{
	pf->var.integer = (unsigned short int)va_arg(va, INTMAX);
}
