/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 22:29:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/24 22:50:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_file_in_dir(char *filename, char *dirname)
{
	DIR				*dir;
	struct dirent	*entry;

	if (!(dir = opendir(dirname)))
		return (0);
	while ((entry = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(entry->d_name, filename))
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int		get_path_and_file_from_str(char *str, char **path, char **file)
{
	int index;

	*path = NULL;
	*file = NULL;
	if ((index = ft_strichr_last(str, '/')) == -1)
	{
		if (!(*path = ft_strdup("")))
			return (1);
		if (!(*file = ft_strdup(str)))
			return (ft_free_turn(path, 1));
	}
	else
	{
		if (!(*path = ft_strndup(str, index + 1)))
			return (1);
		if (!(*file = ft_strnrest(str, index + 1)))
			return (ft_free_turn(path, 1));
	}
	return (0);
}
