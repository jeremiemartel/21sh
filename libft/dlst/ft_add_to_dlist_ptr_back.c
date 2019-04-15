/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_dlist_ptr_back.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:49:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 19:15:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_add_to_dlist_ptr_back(t_dlist **list, void *content, size_t size)
{
	t_dlist *node;

	if (!(node = ft_dlstnew_ptr(content, size)))
		return (1);
	else
		ft_dlstpushback(list, node);
	return (0);
}
