/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_hash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:35:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 09:49:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Functions used to treat hash flag
*/

void		flag_hash_x(t_conv *conv)
{
	if (conv->type == 'x')
		conv->res = ft_strjoin_free("0x", conv->res, 2);
	if (conv->type == 'X')
		conv->res = ft_strjoin_free("0X", conv->res, 2);
}

void		flag_hash_o(t_conv *conv)
{
	conv->res = ft_strjoin_free("0", conv->res, 2);
}

void		flag_hash_f(t_conv *conv)
{
	if (ft_strchr(conv->res, '.') == NULL)
		conv->res = ft_strjoin_free(conv->res, ".", 1);
}
