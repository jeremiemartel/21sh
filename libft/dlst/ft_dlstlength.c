/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlength.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:23:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 20:26:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dlstlength(t_dlist *dlist)
{
	int		length;
	t_dlist	*ptr;
	int		first;

	ptr = dlist;
	first = 1;
	length = 0;
	while ((ptr != dlist && ptr != NULL) || (first && ptr != NULL))
	{
		length++;
		ptr = ptr->next;
		first = 0;
	}
	return (length);
}
