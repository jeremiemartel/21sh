/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 21:43:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:02:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putoctal_max(UINTMAX nb, t_pf *pf)
{
	if ((nb / 8) == 0)
		ft_putchar_buff(nb % 8 + '0', pf);
	else
	{
		ft_putoctal_max((UINTMAX)nb / (UINTMAX)8, pf);
		ft_putchar_buff(nb % 8 + '0', pf);
	}
}
