/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 09:48:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:01:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dprintf(int fd, const char *format, ...)
{
	int		len;
	t_conv	*start;
	va_list	va;

	if (!format)
		return (-1);
	if (!(start = ft_printf_split(format)))
		return (0);
	va_start(va, format);
	ft_printf_args(start, va);
	va_end(va);
	len = ft_dprintf_put_result(fd, start);
	t_conv_free_lst(start);
	return (len);
}
