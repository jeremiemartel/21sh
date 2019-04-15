/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:23:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 18:46:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstpushback(t_dlist **lst, t_dlist *toadd)
{
	t_dlist *ptr;

	ptr = *lst;
	if (*lst == NULL)
		ft_dlstadd(lst, toadd);
	else
	{
		ptr = ptr->prev;
		ptr->next = toadd;
		toadd->prev = ptr;
		toadd->next = *lst;
		(*lst)->prev = toadd;
	}
}
