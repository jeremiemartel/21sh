/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:34:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/23 13:21:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_execute_command_no_path:
**	Command execution prcedure if PATH environment variable is not set,
**	or if the command path substitution failed in using PATH env variable.
**	return Value:
**		sh_process_execute returned value
*/
int		sh_execute_command_no_path(t_context *context)
{
	char	cwd[CWD_LEN];
	char	*full_path;
	int		ret;

	if (((char **)context->params->tbl)[0][0] == '/')
		return (sh_process_execute(context->params->tbl[0], context));
	else
	{
		if (getcwd(cwd, CWD_LEN) == NULL)
			return (FAILURE);
		if (!(full_path = ft_strjoin_3(cwd, "/", context->params->tbl[0])))
			return (FAILURE);
		if (!sh_check_execute(full_path, context->params->tbl[0]))
		{
			free(full_path);
			return (FAILURE);
		}
		ret = sh_process_execute(full_path, context);
		free(full_path);
		return (ret);
	}
}

/*
** sh_execute_command_path:
**	Normal execution procedure (if PATH envvariable is set):
**	Look for the command path, using the PATH env variable, if command is found
**	it process it
**	return Values:
**		-2 : command was not found
**		else : command returned value
*/
int		sh_execute_command_path(t_context *context, char *path_str)
{
	char	**path_split;
	int		i;
	char	*full_path;
	int		ret;

	ret = SUCCESS;
	if (!(path_split = ft_strsplit(path_str, ':')))
		return (FAILURE);
	i = 0;
	while (path_split[i])
	{
		if (get_file_in_dir(context->params->tbl[0], path_split[i]))
		{
			if (!(full_path = ft_strjoin_3(path_split[i], "/",
					context->params->tbl[0])))
				return (FAILURE);
			if (!sh_check_execute(full_path, context->params->tbl[0]))
			{
				free(full_path);
				return (FAILURE);
			}
			ret = sh_process_execute(full_path, context);
			free(full_path);
			ft_strtab_free(path_split);
			return (ret);
		}
		i++;
	}
	ft_strtab_free(path_split);
	return (-2);
}

t_builtin	*sh_execute_find_builtin(t_context *context)
{
	t_list	*head;

	head = context->builtins;
	while(head)
	{
		if (ft_strcmp(((t_builtin*)head->content)->name, context->params->tbl[0]) == 0)
			return (head->content);
		head = head->next;
	}
	return (NULL);
}

int		sh_execute_command(t_context *context)
{
	int			ret;
	char		*path_str;
	t_builtin	*builtin;

	if ((builtin = sh_execute_find_builtin(context)))
		return (builtin->builtin(context->params, context->env));
	if ((path_str = get_env_value((char **)context->env->tbl, "PATH")))
	{
		if ((ret = sh_execute_command_path(context, path_str)) != -2)
			return (ret);
	}
	return (sh_execute_command_no_path(context));
}
