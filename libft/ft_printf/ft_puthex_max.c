/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:54:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:02:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_get_char_from_index(int index, int maj)
{
	if (index <= 9)
		return (index + '0');
	else
	{
		if (maj)
			return (index + 'A' - 10);
		else
			return (index + 'a' - 10);
	}
}

void		ft_puthex_max(UINTMAX nb, int maj, t_pf *pf)
{
	if ((nb / 16) == 0)
		ft_putchar_buff(ft_get_char_from_index(nb % 16, maj), pf);
	else
	{
		ft_puthex_max((UINTMAX)nb / (UINTMAX)16, maj, pf);
		ft_putchar_buff(ft_get_char_from_index(nb % 16, maj), pf);
	}
}
