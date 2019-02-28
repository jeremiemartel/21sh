/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_prec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:35:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 09:49:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** All the functions associated to gestion of precision
** Sorted by conversion type
*/

void		flag_prec_di(t_conv *conv)
{
	int		len;
	char	*buf;

	len = ft_strlen(conv->res);
	if (!ft_isdigit(conv->res[0]))
		len--;
	if (conv->prec <= len)
		return ;
	len = conv->prec - len;
	buf = ft_strnew(len);
	ft_memset(buf, '0', len);
	if (!ft_isdigit(conv->res[0]))
		conv->res = ft_strinsert_free(conv->res, buf, 1, 3);
	else
		conv->res = ft_strjoin_free(buf, conv->res, 3);
}

void		flag_prec_x(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (*conv->res == 0)
		return ;
	if ((conv->conv & FLAG_HASH))
		len -= 2;
	if (conv->prec <= len)
		return ;
	len = conv->prec - len;
	if (conv->conv & FLAG_HASH)
		conv->res = ft_strinsert_free(
			conv->res, ft_memset(ft_strnew(len), '0', len), 2, 3);
	else
		conv->res = ft_strjoin_free(
			ft_memset(ft_strnew(len), '0', len), conv->res, 3);
	return ;
}

void		flag_prec_o(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if ((conv->conv & FLAG_HASH))
		len -= 1;
	if (conv->prec <= len)
		return ;
	len = conv->prec - len;
	if (conv->res[0] == '0' && conv->conv & FLAG_HASH)
		len--;
	conv->res = ft_strinsert_free(
		conv->res, ft_memset(ft_strnew(len), '0', len), 0, 3);
	return ;
}

void		flag_prec_u(t_conv *conv)
{
	int		len;

	len = ft_strlen(conv->res);
	if (conv->prec <= len)
		return ;
	len = conv->prec - len;
	conv->res = ft_strjoin_free(
		ft_memset(ft_strnew(len), '0', len), conv->res, 3);
}
