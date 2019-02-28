/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:24:17 by jmartel           #+#    #+#             */
/*   Updated: 2018/12/07 13:50:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(const char *s1, const char *s2, int param)
{
	char	*buf1;
	char	*buf2;
	char	*res;

	buf1 = (char*)s1;
	buf2 = (char*)s2;
	res = ft_strjoin(s1, s2);
	if (param == 1)
		free(buf1);
	else if (param == 2)
		free(buf2);
	else if (param == 3)
	{
		free(buf1);
		free(buf2);
	}
	return (res);
}
