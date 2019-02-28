/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_new_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 09:28:54 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/22 09:38:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strtab_new_line : clone an array, with one more index
**		if free is true the original tab will be freed
*/

char		**ft_strtab_new_line(char **tab, int free)
{
	int		len;
	int		index;
	char	**res;

	len = ft_strtab_len(tab) + 2;
	if (!(res = malloc(sizeof(*res) * len)))
		return (NULL);
	index = -1;
	while ((tab)[++index])
		if (!(res[index] = ft_strdup((tab)[index])))
		{
			ft_strtab_free(res);
			return (NULL);
		}
	res[index] = 0;
	res[index + 1] = 0;
	if (free)
		ft_strtab_free(tab);
	return (res);
}
