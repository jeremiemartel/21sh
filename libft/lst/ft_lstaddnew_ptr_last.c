/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnew_ptr_last.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:05:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 22:10:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstaddnew_ptr_last(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew(content, size)))
		return (1);
	else
		ft_lstadd_last(list, node);
	return (0);
}
