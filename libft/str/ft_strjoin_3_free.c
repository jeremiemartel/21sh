/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:17:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/04 22:17:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_3_free(char const *s1, char const *s2, char const *s3)
{
	char *res;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	res = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (res == NULL)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_strcpy(res, s1);
	free((char *)s1);
	ft_strcat(res, s2);
	ft_strcat(res, s3);
	return (res);
}
