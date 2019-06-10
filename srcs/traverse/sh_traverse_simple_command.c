/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 15:15:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_simple_command:
**	Traverse used to executed any simple command.
**	In EXECUTE phase : It first call any sons to fill context
**	then it looks for a built in or an executable matching the command name.
**	If any were found it executes it.
**
** return  :
**	FAILURE : malloc error
**	ERROR : command not found
**	SUCCESS : no command were given
**	any value returned by a builtin executed or a process launched
*/
int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		context->redirections = &node->metadata.command_metadata.redirections;
		if ((ret = sh_traverse_tools_browse(node, context)))
			return (ret);
		if (!context->params->tbl[0])
			return (SUCCESS);
		if (!ft_strchr(context->params->tbl[0], '/'))
			ret = sh_traverse_sc_no_slash_cmd(context);
		else
		{
			if (!(context->path = ft_strdup(context->params->tbl[0])))
				return (ft_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
			ret = sh_process_execute(context);
		}
		// NEED TO IMPLEMENT EXECVE ERRORS TREATMENT
		sh_traverse_tools_reset_params(context);
		return (ret);
	}
	else
		return (sh_traverse_tools_browse(node, context));
}

/*
** sh_traverse_sc_no_slash_cmd:
**	Function launching the execution of a process if context->params->tbl[0]
**	do not contain a path (does not contain a '/' character)
**	It try to launch any builtin, then look in $PATH env variable.
**	If any command was found it is launched
**
** return  :
**	FAILURE : malloc error
**	ERROR : command not found
**	any value returned by a builtin executed or a process launched
*/
int		sh_traverse_sc_no_slash_cmd(t_context *context)
{
	if ((context->builtin = sh_builtin_find(context)))
		return (sh_process_execute_builtin(context));
	// undefined behaviour names
	// Looking for functions
	// Reserved utility
	if (sh_traverse_sc_search_in_path(context) == FAILURE)
		return (FAILURE);
	if (context->path)
		return (sh_process_execute(context));
	else
	{
		ft_perror_err(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
		sh_env_vars_update_question_mark(context, 127);
		return (ERROR);
	}
}

/*
** sh_traverse_sc_search_in_dir:
**		Look for any executable matching the context->params->tbl[0],
**		in the directory defined by path and dir
**		If any valid match is ffound, context->path is filled
**
**		return : 
**		FAILURE : malloc error	
**		SUCCESS : any error occur
*/
int		sh_traverse_sc_search_in_dir(char *path, DIR *dir, t_context *context)
{
	t_dirent	*dirent;
	char		*buf;

	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(dirent->d_name, context->params->tbl[0]))
		{
			// ADD PERMISSIONS CHECK
			if (!(buf = ft_strjoin_path(path, dirent->d_name)))
			{
				closedir(dir);
				return (ft_perror(SH_ERR1_MALLOC,
					"traverse_sc_search_in_dir"));
			}
			if (sh_traverse_sc_check_perm(buf,
					context->params->tbl[0]) == FAILURE)
			{
				free(buf);
				continue ;
			}
			context->path = buf;
			closedir(dir);
			return (SUCCESS);
		}
	}
	closedir(dir);
	return (SUCCESS);
}

/*
** sh_traverse_sc_search_in_path:
**	Use the PATH env variable to look for any executable named like
**	context->params->tbl[0], with correct execution rights.
**	If it found a valid match, context->path is filled with path of executable
**	return :
**		FAILURE : malloc error
**		ERROR : $PATH is empty
**		SUCCESS : Any error occured
*/
int		sh_traverse_sc_search_in_path(t_context *context)
{
	char	**split;
	int		i;
	DIR		*dir;
	char	*buffer;

	if (!(buffer = sh_vars_get_value(context->env, context->vars, "PATH")))
		return (ERROR);
	if (!(split = ft_strsplit(buffer, ':')))
		return (FAILURE);
	i = 0;
	while (split[i])
	{
		if (!(dir = opendir(split[i])))
		{
			i++;
			continue ;
		}
		if (sh_traverse_sc_search_in_dir(split[i], dir, context) == FAILURE)
			return (FAILURE);
		if (context->path)
			break ;
		i++;
	}
	ft_strtab_free(split);
	return (SUCCESS);
}

int		sh_traverse_sc_check_perm(char *path, char *command_name)
{
	struct stat		st;

	if (stat(path, &st) == -1)
		return (FAILURE);
	if (access(path, X_OK))
		return (ft_perror(SH_ERR1_PERM_DENIED, command_name));
	if (!S_ISREG(st.st_mode))
		return (ft_perror_err(SH_ERR1_CMD_NOT_FOUND, command_name));
	return (SUCCESS);
}
