/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:31:42 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 09:49:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Fonctions associated to gestion of flags plus and space
*/

void		flag_plus(t_conv *conv, int sign)
{
	if (sign >= 0)
		conv->res = ft_strjoin_free("+", conv->res, 2);
	return ;
}

void		flag_space(t_conv *conv, int sign)
{
	if (sign >= 0)
		conv->res = ft_strjoin_free(" ", conv->res, 2);
	return ;
}
