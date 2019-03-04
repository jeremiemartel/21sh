/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 22:24:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 22:27:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_lstpop_ptr(t_list **list)
{
	t_list *to_free;
	void	*content;

	if (*list)
	{
		to_free = *list;
		content = to_free->content;
		*list = (*list)->next;
		free(to_free);
		return (content);
	}
	return (NULL);
}
