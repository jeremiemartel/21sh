/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_clipboard_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:45:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 15:48:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*refined_str(char *str)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(str);
	if (!(res = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (ft_isascii(str[i]))
			res[i] = str[i];
		else
			res[i] = '?';
		i++;
	}
	res[i] = '\0';
	return (res);
}
