/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:28:36 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/11 19:14:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t		istr;
	size_t		ifind;

	if (*find == 0)
		return ((char*)str);
	istr = 0;
	while (str[istr] && istr < len)
	{
		ifind = 0;
		while (str[istr + ifind] && str[istr + ifind] == find[ifind] \
				&& istr + ifind < len)
			ifind++;
		if (find[ifind] == 0 && str[istr] && istr < len)
			return ((char*)(str + istr));
		istr++;
	}
	return (NULL);
}
