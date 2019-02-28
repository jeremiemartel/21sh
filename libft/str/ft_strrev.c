/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:41:15 by jmartel           #+#    #+#             */
/*   Updated: 2018/12/17 19:34:44 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strswap(char *str1, char *str2)
{
	char	buffer;

	buffer = *str1;
	*str1 = *str2;
	*str2 = buffer;
	return ;
}

void		ft_strrev(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	while (i < len / 2)
	{
		ft_strswap(s + i, s + len - 1 - i);
		i++;
	}
	return ;
}
