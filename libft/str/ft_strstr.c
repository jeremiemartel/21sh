/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:28:13 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/08 12:28:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *find)
{
	size_t		istr;
	size_t		ifind;

	if (*find == 0)
		return ((char*)str);
	istr = 0;
	while (str[istr])
	{
		ifind = 0;
		while (str[istr + ifind] && str[istr + ifind] == find[ifind])
			ifind++;
		if (find[ifind] == 0 && str[istr])
			return ((char*)(str + istr));
		istr++;
	}
	return (NULL);
}
