/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:09:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 21:21:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **list, void (*del) (void *, size_t))
{
	void	*content;
	t_dlist *ptr;
	t_dlist *next;

	while (*list != NULL)
	{
		ptr = *list;
		next = (*list)->next;
		content = ptr->content;
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
