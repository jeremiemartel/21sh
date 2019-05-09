/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:53:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/09 15:53:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_xy	get_position(int cursor)
{
	t_xy res;

	res.x = cursor % g_glob.winsize.ws_col;
	res.y = cursor / g_glob.winsize.ws_col;
	return (res);
}

int		xy_is_equal(t_xy xy1, t_xy xy2)
{
	return (xy1.x == xy2.x && xy1.y == xy2.y);
}
