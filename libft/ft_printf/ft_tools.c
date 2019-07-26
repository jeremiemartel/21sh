/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:04:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/27 00:31:44 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_no_number(t_pf *pf)
{
	pf->parse_padding = 0;
	pf->parse_precision = 0;
}

INTMAX		ft_abs_max(INTMAX a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

double		ft_fabs(double a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}
