/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dystr_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 08:41:05 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 09:16:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_dystr_new:
**		Create a new t_dystr object, malloc it str to size.
**		If str exist it is copied into dystr->str
**		return value:
**			NULL : if any error occur
**			new object address else
*/

t_dystr		*ft_dystr_new(char *str, size_t size, size_t len)
{
	t_dystr		*dystr;

	if (!(dystr = malloc(sizeof(*dystr))))
		return (NULL);
	if (!(dystr->str = malloc(sizeof(char) * (size + 1))))
	{
		free(dystr);
		return (NULL);
	}
	if (str)
		ft_strncpy(dystr->str, str, len);
	if (!str)
		dystr->len = 0;
	else
		dystr->len = len;
	dystr->size = size;
	return (dystr);
}
