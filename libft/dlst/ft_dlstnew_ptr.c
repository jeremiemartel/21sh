/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:59:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 18:11:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew_ptr(void const *content, size_t content_size)
{
	t_dlist	*new_node;

	if (!(new_node = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	if (content == NULL)
	{
		new_node->content = NULL;
		new_node->content_size = 0;
	}
	else
	{
		new_node->content = (void *)content;
		new_node->content_size = content_size;
	}
	new_node->next = new_node;
	new_node->prev = new_node;
	return (new_node);
}
