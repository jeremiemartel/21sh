/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:35:51 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:37:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Main function :
** 	-calling split to create the t_conv linked list
** 	-calling ft_printf_args fill the linked list ->res field
** 	-printing all results with ft_printf_put_result
*/

int			ft_printf(const char *format, ...)
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
	len = ft_printf_put_result(start);
	t_conv_free_lst(start);
	return (len);
}

/*
** Browsing the s_conv list, to fill the links function of their type
*/

int			ft_printf_args(t_conv *head, va_list va)
{
	while (head)
	{
		if (head->type == 'd' || head->type == 'i')
			fill_di(va, head);
		else if (head->type == 'x' || head->type == 'X')
			fill_x(va, head);
		else if (head->type == 'o')
			fill_o(va, head);
		else if (head->type == 'u')
			fill_u(va, head);
		else if (head->type == 'f')
			fill_f(va, head);
		else if (head->type == 'p')
			fill_p(va, head);
		else if (head->type == 's')
			fill_s(va, head);
		else if (head->type == 'c')
			fill_c(va, head);
		else if (head->type == '%')
			fill_perc(head);
		else if (head->type == 'b')
			fill_b(va, head);
		head = head->next;
	}
	return (0);
}
