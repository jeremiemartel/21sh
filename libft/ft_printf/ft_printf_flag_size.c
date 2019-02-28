/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:38:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 09:49:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** All the functions associated to gestion of size, minus and zero flags
** Sorted by conversion type
*/

void		flag_size_di(t_conv *conv)
{
	int			len;
	int			i;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	i = 0;
	if (conv->res && conv->res && !ft_isdigit(conv->res[0]))
		i = 1;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else if (conv->conv & FLAG_ZERO && conv->prec == NO_PREC)
		conv->res = ft_strinsert_free(
			conv->res, ft_memset(ft_strnew(len), '0', len), i, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}

void		flag_size_x(t_conv *conv)
{
	int		len;
	int		i;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	i = 0;
	len = conv->size - len;
	if (conv->conv & FLAG_HASH)
		i = 2;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else if (conv->conv & FLAG_ZERO && conv->prec == NO_PREC)
		conv->res = ft_strinsert_free(
			conv->res, ft_memset(ft_strnew(len), '0', len), i, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}

void		flag_size_o(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else if (conv->conv & FLAG_ZERO && conv->prec == NO_PREC)
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), '0', len), conv->res, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}

void		flag_size_u(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else if ((conv->conv & FLAG_ZERO) && conv->prec == NO_PREC)
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), '0', len), conv->res, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}

void		flag_size_f(t_conv *conv)
{
	int			len;
	int			i;

	len = ft_strlen(conv->res);
	if (len >= conv->size)
		return ;
	i = 0;
	if (!ft_isdigit(conv->res[0]))
		i = 1;
	len = conv->size - len;
	if (conv->conv & FLAG_MINUS)
		conv->res = ft_strjoin_free(
			conv->res, ft_memset(ft_strnew(len), ' ', len), 3);
	else if (conv->conv & FLAG_ZERO)
		conv->res = ft_strinsert_free(
			conv->res, ft_memset(ft_strnew(len), '0', len), i, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), ' ', len), conv->res, 3);
}
