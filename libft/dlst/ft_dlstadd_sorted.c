/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_sorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:21:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/26 23:13:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_node_next_to_node(t_dlist *node, t_dlist *to_add)
{
	t_dlist *tmp;

	tmp = node->next;
	node->next = to_add;
	to_add->prev = node;
	to_add->next = tmp;
	tmp->prev = to_add;
}

int		ft_dlstadd_sorted(t_dlist **dlst,
			void *content, int (*sort)(void*, void *))
{
	int		first;
	t_dlist	*to_add;
	t_dlist	*ptr;

	if (!(to_add = ft_dlstnew_ptr(content, sizeof(content))))
		return (1);
	ptr = *dlst;
	first = 1;
	while ((ptr != *dlst && ptr != NULL) || (first && ptr != NULL))
	{
		if (sort(ptr->content, content) > 0)
		{
			add_node_next_to_node(ptr->prev, to_add);
			return (0);
		}
		ptr = ptr->next;
		first = 0;
	}
	add_node_next_to_node(ptr->prev, to_add);
	return (0);
}
