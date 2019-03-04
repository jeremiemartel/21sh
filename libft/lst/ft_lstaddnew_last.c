/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnew_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:55:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 21:04:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstaddnew_last(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew(content, size)))
		return (1);
	else
		ft_lstadd_last(list, node);
	return (0);
}
