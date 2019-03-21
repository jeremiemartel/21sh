/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_tab_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 01:43:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/21 01:43:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dy_tab_init(t_dy_tab *dy_tab, size_t max_size)
{
	dy_tab->current_size = 0;
	dy_tab->max_size = max_size;
	if (!(dy_tab->tbl = (void **)ft_memalloc(max_size * (sizeof(void *) + 1))))
		return (1);
	return (0);
}
