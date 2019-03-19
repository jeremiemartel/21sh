/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dystr_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 09:05:23 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 10:26:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_dystr_realloc:
**		Improve size of str in dystr struct. Size is doubled.
**	return value:
**		NULL if any error occured
**		dystr address else
*/

t_dystr		*ft_dystr_realloc(t_dystr *dystr)
{
	char	*buf;

	if (!(buf = ft_memalloc(sizeof(char) * (dystr->size * 2 + 1))))
	{
		ft_dystr_free(dystr);
		return (NULL);
	}
	ft_strncpy(buf, dystr->str, dystr->len);
	free(dystr->str);
	dystr->size *= 2;
	return (dystr);
}
