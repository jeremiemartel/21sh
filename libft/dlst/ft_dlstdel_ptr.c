/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:15:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 19:30:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel_ptr(t_dlist **list)
{
	t_dlist *first;

	first = *list;
	while (first != NULL)
		ft_dlstpop_ptr(&(*list)->next);
}
