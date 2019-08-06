/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:43:40 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 22:43:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new_str(char *str)
{
	t_dy_str	*res;
	int			len;

	len = ft_strlen(str);
	if (!(res = malloc(sizeof(*res))))
		return (NULL);
	if (!(res->str = ft_strdup(str)))
	{
		free(res);
		return (NULL);
	}
	res->max_size = len;
	res->current_size = len;
	return (res);
}
