/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_cpy_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:58:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/16 16:58:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dy_str_cpy_str(t_dy_str *dy_str, char *str)
{
	int len;

	len = ft_strlen(str);
	ft_bzero(dy_str->str, dy_str->max_size);
	while ((int)dy_str->max_size < len)
	{
		if (ft_dy_str_realloc(dy_str))
			return (1);
	}
	ft_memcpy(dy_str->str, str, len);
	dy_str->current_size = len;
	return (0);
}
