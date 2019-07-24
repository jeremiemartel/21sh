/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 16:42:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:02:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_max(UINTMAX nb, t_pf *pf)
{
	if ((UINTMAX)((UINTMAX)nb / (UINTMAX)10) == 0)
		ft_putchar_buff(nb % 10 + '0', pf);
	else
	{
		ft_putnbr_max((UINTMAX)((UINTMAX)nb / (UINTMAX)10), pf);
		ft_putchar_buff(nb % 10 + '0', pf);
	}
}
