/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_where.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:09:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/12 14:32:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_where_is_ok(char *path, t_dirent *dirent)
{
	char	*name;

	name = ft_strrchr(path, '/');
	if (!name || !*name)
		return (0);
	if (!(dirent->d_type & DT_REG))
		return (0);
	if (!name || *name == '.')
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

static int		sh_where_binaries_readdir(char *path, DIR *dir, t_context *context)
{
	t_dirent	*dirent;
	char		*buf;

	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(*context->params->tbl, dirent->d_name))
		{
			if (!sh_where_is_ok(path, dirent))
				continue ;
			if (!(buf = ft_strjoin_path(path, dirent->d_name)))
			{
				ft_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, buf);
				free(buf);
				return (FAILURE);
			}
			ft_dprintf(context->fd[FD_OUT], "%s\n", buf);
			free(buf);
		}
	}
	return (SUCCESS);
}

static int		sh_where_binaries(t_context *context)
{
	char	**split;
	int		i;
	DIR		*dir;

	split = ft_strsplit(sh_vars_get_value(context->env, NULL, "PATH"), ':');
	if (!(split))
		return (FAILURE);
	i = 0;
	while (split[i])
	{
		if (!(dir = opendir(split[i])))
		{
			i++;
			continue ;
		}
		sh_where_binaries_readdir(split[i], dir, context);
		closedir(dir);
		i++;
	}
	ft_strtab_free(split);
	return (SUCCESS);
}

int				sh_builtin_where(t_context *context)
{
	int		i;

	i = 1;
	context->params->tbl++;
	while (*context->params->tbl)
	{
		if (sh_builtin_find(context))
			ft_printf("%s: %s built-in command\n",context->params->tbl[0] , SH_NAME);
		if (sh_where_binaries(context) == FAILURE)
		{
			context->params->tbl -= i;
			return (FAILURE);
		}
		context->params->tbl++;
		i++;
	}
	context->params->tbl -= i;
	return (SUCCESS);
}
