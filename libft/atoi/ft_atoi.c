/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:03:12 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:39:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		sym;
	int		res;

	res = 0;
	sym = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v' \
				|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sym = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		res = 10 * res + *str - '0';
		str++;
	}
	return (sym * res);
}
