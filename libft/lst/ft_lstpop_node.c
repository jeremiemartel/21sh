/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 00:12:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/06 11:45:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstpop_node(t_list **list)
{
	t_list	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		*list = (*list)->next;
		ptr->next = NULL;
		return (ptr);
	}
	return (NULL);
}
