/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:23:41 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/22 12:30:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_puttab_int(int *tab, int size)
{
	int		i;

	if (tab == NULL)
		return ;
	i = 0;
	ft_putchar('|');
	while (i < size)
	{
		ft_putnbr(tab[i]);
		ft_putchar('|');
		i++;
	}
	return ;
}
