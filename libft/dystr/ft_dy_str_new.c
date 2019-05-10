/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:53:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 12:40:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new(size_t max_size)
{
	t_dy_str *res;

	if (!(res = (t_dy_str *)malloc(sizeof(t_dy_str))))
		return (NULL);
	res->current_size = 0;
	res->max_size = max_size;
	if (max_size > 0)
	{
		if (!(res->str = (char *)ft_memalloc(max_size * (sizeof(char) + 1))))
		{
			free(res);
			return (NULL);
		}
	}
	return (res);
}
