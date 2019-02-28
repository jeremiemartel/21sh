/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:59:55 by jmartel           #+#    #+#             */
/*   Updated: 2018/12/30 16:16:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_path(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL || *s1 == 0)
		return (ft_strdup(s2));
	else if (s2 == NULL || *s2 == 0)
		return (ft_strdup(s1));
	if (ft_strcmp(s1, "/") == 0)
		return (ft_strjoin_free(s1, s2, 0));
	res = (char*)malloc(sizeof(*res) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i++] = '/';
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = 0;
	return (res);
}
