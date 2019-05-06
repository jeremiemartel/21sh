/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substitute_dy_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:54:15 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/26 23:16:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_decal_rest(t_dy_str *dy_str, int index, int len)
{
	int i;

	if (len >= 0)
	{
		i = dy_str->current_size;
		while (i >= index)
		{
			dy_str->str[i + len] = dy_str->str[i];
			i--;
		}
	}
	else
	{
		i = index;
		while (i <= (int)dy_str->current_size)
		{
			dy_str->str[i + len] = dy_str->str[i];
			i++;
		}
	}
}

static void	ft_inject_str_in_str(t_dy_str *dy_str,
			char *to_inject, int start_index)
{
	int		i;
	int		j;

	i = start_index;
	j = 0;
	while (to_inject[j])
	{
		dy_str->str[i] = to_inject[j];
		j++;
		i++;
	}
}

/*
** realloc d_str and inject to_inject at the index_to_inject at the place of
** the len characters starting from that index
*/

int			ft_substitute_dy_str(t_dy_str *d_str, char *to_inject,
				int index_to_inject, int len)
{
	int necessary_size;
	int to_inject_len;

	to_inject_len = ft_strlen(to_inject);
	necessary_size = d_str->current_size - len + to_inject_len;
	while ((int)d_str->max_size < necessary_size)
	{
		if (ft_dy_str_realloc(d_str))
			return (1);
	}
	ft_decal_rest(d_str, index_to_inject + len, to_inject_len - len);
	ft_inject_str_in_str(d_str, to_inject, index_to_inject);
	d_str->current_size = necessary_size;
	return (0);
}
