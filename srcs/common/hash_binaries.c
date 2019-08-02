/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_binaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:55:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 17:18:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_binary	*sh_new_binary(char *path, char *name)
{
	t_binary *res;

	if (!(res = (t_binary *)malloc(sizeof(t_binary))))
		return (NULL);
	res->hits = 1;
	if (!(res->path = ft_strdup(path)))
	{
		free(res);
		return (NULL);
	}
	if (!(res->name = ft_strdup(name)))
	{
		free(res->path);
		free(res);
		return (NULL);
	}
	return (res);
}

int			compare_str_to_binary(void *str, void *binary)
{
	return (ft_strcmp((char *)str, ((t_binary *)(binary))->name));
}

int			sh_update_hash_table(t_shell *shell, char *path, char *name)
{
	t_binary *res;

	if (!(res = sh_new_binary(path, name)))
		return (FAILURE);
	if (ft_hash_table_add(shell->binaries, res, res->name, ft_hash_str))
		return (FAILURE);
	return (SUCCESS);
}
