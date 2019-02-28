/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstput_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:37:19 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/13 18:37:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstput_fd(t_list *start, int fd)
{
	while (start != NULL)
	{
		write(fd, start->content, start->content_size);
		ft_putstr("-->");
		start = start->next;
	}
	ft_putstr("NULL");
	return ;
}
