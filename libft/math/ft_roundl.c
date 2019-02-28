/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roundl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:39:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:39:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_roundl(long double x)
{
	long long	nb;

	if (x < 0)
		x -= 0.4999999;
	else
		x += 0.4999999;
	nb = (long long)x;
	return ((long double)nb);
}
