/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:39:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:16:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_2_bytes_len(unsigned char str[4], int value)
{
	str[0] = 192 | ((value >> 6) & 31);
	str[1] = 128 | (value & 63);
}

int		ft_put_wchar(int value, t_pf *pf)
{
	int				len;
	unsigned char	str[4];
	int				i;

	ft_bzero((char *)str, 4);
	if ((len = ft_wchar_len(value)) == -1)
		return (-1);
	if (len == 1)
		str[0] = value;
	else if (len == 2)
		ft_2_bytes_len(str, value);
	else if (len == 3)
		ft_3_bytes_len(str, value);
	else
		ft_4_bytes_len(str, value);
	i = 0;
	if ((unsigned int)len <= MY_MB_CUR_MAX)
	{
		while (i < len && (unsigned int)i < MY_MB_CUR_MAX)
			ft_putchar_buff(str[i++], pf);
	}
	else
		ft_putchar_buff(value, pf);
	return (0);
}
