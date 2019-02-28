/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:52:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:26:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_put_result(t_conv *head)
{
	int		len;

	len = 0;
	while (head)
	{
		len += ft_strlen(head->res);
		ft_putstr(head->res);
		if (head->type == 'c')
		{
			if (head->size == NO_SIZE && *head->res == 0)
			{
				ft_putchar(0);
				len++;
			}
			else if (head->size != NO_SIZE
				&& (int)ft_strlen(head->res) < head->size)
			{
				ft_putchar(0);
				len++;
			}
		}
		head = head->next;
	}
	return (len);
}

int			ft_dprintf_put_result(int fd, t_conv *head)
{
	int		len;

	len = 0;
	while (head)
	{
		len += ft_strlen(head->res);
		ft_putstr_fd(head->res, fd);
		if (head->type == 'c')
		{
			if (head->size == NO_SIZE && *head->res == 0)
			{
				ft_putchar_fd(0, fd);
				len++;
			}
			else if (head->size != NO_SIZE
				&& (int)ft_strlen(head->res) < head->size)
			{
				ft_putchar_fd(0, fd);
				len++;
			}
		}
		head = head->next;
	}
	return (len);
}
