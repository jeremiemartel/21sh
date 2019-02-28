/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:38:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/02/27 09:22:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_lstdelone : delete a link in a chained link,
**		if param is non-null it's also free the content
*/

static void		ft_lstdelone_del(t_list *elem, int param)
{
	if (param && elem->content)
		free(elem->content);
	free(elem);
}

void			ft_lstdelone(t_list **start, t_list *elem, int param)
{
	t_list	*prev;
	t_list	*head;

	if (!start || !*start)
		return ;
	prev = NULL;
	head = *start;
	while (head->next && head != elem)
	{
		prev = head;
		head = head->next;
	}
	if (!prev && head == elem)
	{
		*start = head->next;
		ft_lstdelone_del(head, param);
	}
	else if (head == elem)
	{
		prev->next = head->next;
		ft_lstdelone_del(head, param);
	}
}
