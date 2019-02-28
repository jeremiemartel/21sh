/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_prec2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:46:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 09:49:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** All the functions associated to gestion of precision
** Sorted by conversion type
*/

void		flag_prec_s(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (len >= conv->prec)
		conv->res = ft_strsub(conv->res, 0, conv->prec);
	return ;
}
