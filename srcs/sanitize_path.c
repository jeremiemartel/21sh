/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:53:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/30 13:53:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	end_with_char(char *str, char c)
{
       int i;

       i = 0;
       while (str[i])
               i++;
       if (--i >= 0 && str[i] == c)
               return (FAILURE);
       return (SUCCESS);
}

char		*ft_get_previous_directory(char *current_directory)
{
	int i;
	int index;

	index = -1;
	i = 0;
	while (current_directory[i])
	{
		if (current_directory[i] == '/')
			index = i;
		i++;
	}
	if (index == 0 && i == 1)
		return (ft_strdup("/"));
	else
		return (ft_strndup(current_directory, ft_max(1, index)));
}

char		*get_first_path_from_path(char **path)
{
	int		i;
	char	*added_path;

	i = 0;
	while (*(*path + i) && *(*path + i) != '/')
		i++;
	if (!(added_path = ft_strndup(*path, i)))
		return ("NULL");
	if (*(*path + i))
		*path += i + 1;
	else
		*path += i;
	return (added_path);
}

int			add_to_path_dot_dot(char **old_path)
{
	int		i;
	int		index;
	char	*res;

	i = 0;
	index = -1;
	while ((*old_path)[i])
	{
		if ((*old_path)[i] == '/')
			index = i;
		i++;
	}
	if (index == -1)
		return (-1);
	if (!(res = ft_strndup(*old_path, ft_max(1, index))))
		return (1);
	free(*old_path);
	*old_path = res;
	return (0);
}

int			add_to_path_pwd(char **old_path, char *partial_path)
{
	char *tmp;
	char *res;

	if (!ft_strcmp(partial_path, ".."))
		return (add_to_path_dot_dot(old_path));
	else if (ft_strcmp(partial_path, ".") && ft_strcmp(partial_path, ""))
	{
		tmp = *old_path;
		if (!end_with_char(*old_path, '/'))
		{
			if (!(res = ft_strjoin_3(*old_path, "/", partial_path)))
				return (1);
		}
		else
		{
			if (!(res = ft_strjoin(*old_path, partial_path)))
				return (1);
		}
		*old_path = res;
		free(tmp);
		return (0);
	}
	else
		return (0);
}

char		*get_sanitized_path_from_old(char *old_pwd, char *path)
{
	char	*res;
	char	*partial_path;

	if (!(res = ft_strdup(old_pwd)))
		return (NULL);
	while (*path)
	{
		if (!(partial_path = get_first_path_from_path(&path)))
			return (ft_free_turn_str(&res, NULL));
		if (add_to_path_pwd(&res, partial_path))
			return (ft_free_turn_strs(&res, &partial_path, NULL));
		free(partial_path);
	}
	return (res);
}
