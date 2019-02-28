/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:01:50 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/08 12:01:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if (s[i] == (char)c)
		return ((char*)(s + i));
	else
		i--;
	while (i >= 0 && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return ((char*)(s + i));
	else
		return (NULL);
}
