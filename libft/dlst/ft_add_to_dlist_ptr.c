/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_dlist_ptr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:47:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/11 12:11:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_add_to_dlist_ptr(t_dlist **list, void *content, size_t size)
{
	t_dlist *node;

	if (!(node = ft_dlstnew_ptr(content, size)))
		return (1);
	else
		ft_dlstadd(list, node);
	return (0);
}
