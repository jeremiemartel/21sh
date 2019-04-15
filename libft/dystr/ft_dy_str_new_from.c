/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new_from.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:10:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 15:10:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new_from(char *str)
{
	t_dy_str *res;
	int len;

	len = ft_strlen(str);
	if (!(res = ft_dy_str_new(len)))
		return (NULL);
	ft_memcpy(res->str, str, len);
	res->current_size = len;
	return (res);
}
