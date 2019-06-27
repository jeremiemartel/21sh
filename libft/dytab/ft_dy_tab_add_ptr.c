/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_tab_add_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:22:51 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/25 16:52:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dy_tab_add_ptr(t_dy_tab *d_tab, void *to_add)
{
	if (d_tab->current_size >= d_tab->max_size - 1)
	{
		if (ft_dy_tab_realloc(d_tab))
			return (1);
	}
	d_tab->tbl[d_tab->current_size++] = to_add;
	d_tab->tbl[d_tab->current_size] = 0;
	return (0);
}
