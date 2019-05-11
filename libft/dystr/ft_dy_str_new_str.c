/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:10:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 15:10:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new_str(char *str)
{
	t_dy_str *res;
	int len;

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
