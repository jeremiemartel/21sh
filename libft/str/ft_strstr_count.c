/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/11 13:45:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstr_count(char *str, char *pattern)
{
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == pattern[0])
		{
			j = 1;
			while (str[i + j] == pattern[j] && str[i + j] && pattern[j])
				j++;
			if (pattern[j] == 0)
			{
				i += j - 1;
				res++;
			}
		}
		i++;
	}
	return (res);
}
