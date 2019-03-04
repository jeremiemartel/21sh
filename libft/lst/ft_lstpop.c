/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 22:20:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 22:26:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpop(t_list **list)
{
	t_list *to_free;

	if (*list)
	{
		to_free = *list;
		*list = (*list)->next;
		free(to_free->content);
		free(to_free);
	}
}
