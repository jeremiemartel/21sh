/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:39:25 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 12:42:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new_ptr(char *ptr)
{
	t_dy_str *res;
	int		len;

	len = ft_strlen(ptr);
	if (!(res = ft_dy_str_new(0)))
		return (NULL);
	res->str = ptr;
	res->current_size = len;
	res->max_size = len;
	return (res);
}
