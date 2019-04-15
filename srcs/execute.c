/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:34:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 19:45:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		execute_command_no_path(t_context *context)
{
	char	cwd[CWD_LEN];
	char	*full_path;

	if (shell->params[0][0] == '/')
		return (process_execute(context->params->str[0], context));
	else
	{
		if (getcwd(cwd, CWD_LEN) == NULL)
			return (1);
		if (!(full_path = ft_strjoin_3(cwd, "/", context->params->str[0])))
			return (1);
		if (process_execute(full_path, shell) == -1)
			return (ft_free_turn(full_path, -1));
		free(full_path);
		return (1);
	}
	return (0);
}

int		execute_command_path(t_context *context, char *path_str)
{
	char	**path_split;
	int		i;
	char	*full_path;
	int		ret;

	ret = 0;
	if (!(path_split = ft_strsplit(path_str, ':')))
		return (1);
	i = 0;
	while (path_split[i])
	{
		if (get_file_in_dir(context->params->str[0], path_split[i]))
		{
			if (!(full_path = ft_strjoin_3(path_split[i], "/",
					context->params->str[0])))
				return (1);
			ret = process_execute(full_path, context);
			free(full_path);
			ft_free_split(path_split);
			return (ret == -1 ? -1 : 0);
		}
		i++;
	}
	ft_free_split(path_split);
	return (2);
}

int		execute_command(t_context *context)
{
	char	*path_str;
	int		ret;

//	if (execute_builtin(context))
//		return (0);
	if ((path_str = get_env_value((char **)context->env->tbl, "PATH")))
	{
		if ((ret = execute_command_path(context, path_str)) != 2)
			return (ret);
	}
	return (execute_command_no_path(context));
}
