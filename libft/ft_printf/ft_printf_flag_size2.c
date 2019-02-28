/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_size2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:44:21 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 09:49:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** All the functions associated to gestion of size, minus and zero flags
** Sorted by conversion type
*/

void		flag_size_p(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}

void		flag_size_s(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 2);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 1);
}

void		flag_size_c(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 2);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 1);
}

void		flag_size_perc(t_conv *conv)
{
	int		len;

	if (conv->size < 1)
		return ;
	len = conv->size - 1;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else if (conv->conv & FLAG_ZERO)
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), '0', len), conv->res, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}
