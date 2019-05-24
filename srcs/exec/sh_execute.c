/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:34:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/24 12:10:33 by jmartel          ###   ########.fr       */
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
	// char	*full_path;

	if (((char **)context->params->tbl)[0][0] == '/')
		return (SUCCESS);//sh_process_execute(context->params->tbl[0], context));
	else
	{
		if (getcwd(cwd, CWD_LEN) == NULL)
			return (FAILURE);
		// if (!(full_path = ft_strjoin_3(cwd, "/", context->params->tbl[0])))
		// 	return (FAILURE);
		// if (!sh_check_execute(full_path, context->params->tbl[0]))
		if (!sh_check_execute(context->params->tbl[0], context->params->tbl[0]))
		{
			// free(full_path);
			return (FAILURE);
		}
		// free(context->params->tbl[0]);
		// context->params->tbl[0] = full_path;
		return (SUCCESS);
	}
}

/*
** sh_execute_command_path:
**	Normal execution procedure (if PATH env variable is set):
**	Look for the command path, using the PATH env variable, if command is found
**	it process it
**	return Values:
**		0 found
**		1 not found
**		2 error
*/
int		sh_execute_command_path(t_context *context)
{
	char	**path_split;
	int		i;
	char	*full_path;
	char	*path_str;

	path_str = get_env_value((char **)context->env->tbl, "PATH");
	if(!path_str || !*path_str)
		return (1);
	if (!(path_split = ft_strsplit(path_str, ':')))
		return (FAILURE);
	i = 0;
	while (path_split[i])
	{
		if (get_file_in_dir(context->params->tbl[0], path_split[i]))
		{
			if (!(full_path = ft_strjoin_3(path_split[i], "/", context->params->tbl[0])))
				return (FAILURE);
			if (sh_check_execute(full_path, context->params->tbl[0]) == FAILURE)
			{
				free(full_path);
				return (FAILURE);
			}
			free(context->params->tbl[0]);
			context->params->tbl[0] = full_path;
			ft_strtab_free(path_split);
			return (SUCCESS);
		}
		i++;
	}
	ft_strtab_free(path_split);
	return (-2);
}

int		sh_execute_command(t_context *context)
{
	int			ret;

	if (!(context->builtin = sh_builtin_find(context)))
	{
		if ((ret = sh_execute_command_path(context)))
		{
			if (ret == 2)
				return (FAILURE);
			// else
			// {
			// 	if (sh_execute_command_no_path(context) == FAILURE)
			// 		return (FAILURE);
			// }
		}
	}
	if (sh_verbose_exec())
	{
		ft_printf(BLUE"parameters\n"EOC);
		ft_strtab_put((char**)context->params->tbl);
		ft_printf("\n");
	}
	if (context->builtin)
		sh_process_execute_builtin(context);
	else
		sh_process_execute(context);
	return (SUCCESS);
}
