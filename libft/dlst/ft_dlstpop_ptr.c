/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:25:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/26 23:14:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_dlstpop_ptr(t_dlist **list)
{
	void	*content;
	t_dlist *ptr;
	t_dlist *next;

	if (*list != NULL)
	{
		ptr = *list;
		next = (*list)->next;
		content = ptr->content;
		(*list)->prev->next = (*list)->next;
		(*list)->next->prev = (*list)->prev;
		free(ptr);
		if (*list == next)
			*list = NULL;
		else
			*list = next;
		return (content);
	}
	return (NULL);
}
