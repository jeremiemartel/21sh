/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:09:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:14:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **list, void (*del) (void *, size_t))
{
	t_dlist *ptr;
	t_dlist *next;

	while (*list != NULL)
	{
		ptr = *list;
		next = (*list)->next;
		(*list)->prev->next = (*list)->next;
		(*list)->next->prev = (*list)->prev;
		del(ptr->content, ptr->content_size);
		free(ptr);
		if (*list == next)
			*list = NULL;
		else
			*list = next;
	}
}
