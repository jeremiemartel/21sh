/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 09:48:50 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:29:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_asprintf(const char *format, ...)
{
	t_conv	*start;
	va_list	va;
	char	*res;

	if (!format)
		return (NULL);
	if (!(start = ft_printf_split(format)))
		return (NULL);
	va_start(va, format);
	ft_printf_args(start, va);
	va_end(va);
	res = ft_asprintf_result(start);
	t_conv_free_lst(start);
	return (res);
}

char		*ft_asprintf_result(t_conv *start)
{
	char	*res;

	if (!start)
		return (NULL);
	if (!(res = ft_strdup(start->res)))
		return (NULL);
	start = start->next;
	while (start)
	{
		if (!(res = ft_strjoin_free(res, start->res, 1)))
			return (NULL);
		start = start->next;
	}
	return (res);
}
