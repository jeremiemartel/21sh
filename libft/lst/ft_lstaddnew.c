/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:09:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 22:09:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstaddnew(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew_value(content, size)))
		return (1);
	else
		ft_lstadd(list, node);
	return (0);
}
