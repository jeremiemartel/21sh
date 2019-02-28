/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:38:43 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/11 19:38:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*buf1;
	t_list	*buf2;
	t_list	*start;

	if (!f || !lst)
		return (NULL);
	start = f(lst);
	lst = lst->next;
	buf2 = start;
	while (lst != NULL)
	{
		buf1 = f(lst);
		buf2->next = buf1;
		buf2 = buf1;
		lst = lst->next;
	}
	buf2->next = NULL;
	return (start);
}
