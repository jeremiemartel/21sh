/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter_inv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:32:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/26 23:13:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstiter_inv(t_dlist *dlist, void (*f)(t_dlist *elem))
{
	t_dlist *ptr;
	int		first;

	ptr = dlist->prev;
	first = 1;
	while ((ptr != dlist->prev && ptr != NULL) || (first && ptr != NULL))
	{
		f(ptr);
		ptr = ptr->prev;
		first = 0;
	}
}
