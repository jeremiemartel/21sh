/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 00:12:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 17:01:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstpop_node(t_list **list)
{
	void	*content;
	t_list	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		content = ptr->content;
		*list = (*list)->next;
		ptr->next = NULL;
		return (ptr);
	}
	return (NULL);
}
