/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 07:48:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/09 09:45:44 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *str, size_t n)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = 0;
	while (str[len] && len < n)
		len++;
	if (!(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	res[len] = 0;
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}
