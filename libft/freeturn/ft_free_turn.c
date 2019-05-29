/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_turn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:51:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/27 22:46:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_turn_strs(char **to_del, char **to_del2, char *res)
{
	ft_strdel(to_del);
	ft_strdel(to_del2);
	return (res);
}

char	*ft_free_turn_str(char **to_del, char *res)
{
	ft_strdel(to_del);
	return (res);
}

int		ft_del_turn(void **to_del, int res)
{
	if (*to_del != NULL)
	{
		free(*to_del);
		*to_del = NULL;
	}
	return (res);
}

int		ft_del_turn_char(char **to_del, int res)
{
	if (*to_del != NULL)
	{
		free(*to_del);
		*to_del = NULL;
	}
	return (res);
}

int		ft_free_turn(void *str, int ret)
{
	free(str);
	return (ret);
}
