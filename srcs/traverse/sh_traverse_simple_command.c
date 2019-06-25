/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/24 10:58:19 by jmartel          ###   ########.fr       */
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
				return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
			if (sh_traverse_sc_check_perm(context->path, context->params->tbl[0]) != SUCCESS)
				ret = ERROR;
			else
				ret = sh_process_execute(context);
		}
		sh_traverse_tools_reset_params(context);
		return (ret);
	}
	else
		return (sh_traverse_tools_browse(node, context));
}

int		sh_traverse_sc_search_in_hash(t_context *context)
{
	t_binary		*binary;
	t_hash_finder	finder;

	finder = ft_hash_table_find(context->shell->binaries,
		context->params->tbl[0], ft_hash_str, compare_str_to_binary);
	if (finder.found)
	{
		binary = (t_binary *)finder.content;
		binary->hits++;
		if (access(binary->path, F_OK))
		{
			if (finder.prev)
				finder.prev->next = finder.prev->next->next;
			else
				*finder.list = (*(finder.list))->next;
			sh_free_binary(binary);
			free(finder.current);
			return (ERROR);
		}
		if (sh_traverse_sc_check_perm(binary->path, binary->name) == ERROR)
			return (SUCCESS); // Exists but no permisssions !
		context->path = ft_strdup(binary->path);
		return (SUCCESS);
	}
	else
		return (ERROR);
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
		return (sh_exec_builtin(context));
	if (sh_traverse_sc_search_in_hash(context) != SUCCESS)
	{
		if (sh_traverse_sc_search_in_path(context) == FAILURE)
			return (FAILURE);
	}
	if (context->path)
		return (sh_process_execute(context));
	else
	{
		sh_perror_err(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
		sh_env_vars_update_question_mark(context, 127);
		return (SUCCESS);
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
			if (!(buf = ft_strjoin_path(path, dirent->d_name)))
			{
				closedir(dir);
				return (sh_perror(SH_ERR1_MALLOC,
					"traverse_sc_search_in_dir"));
			}
			if (sh_traverse_sc_check_perm(buf,
					context->params->tbl[0]) != SUCCESS)
			{
				free(buf);
				continue ;
			}
			context->path = buf;
			closedir(dir);
			if (sh_update_hash_table(context->shell,
				context->path, context->params->tbl[0]) != SUCCESS)
				return (FAILURE);
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

/*
** sh_traverse_sc_check_perm:
**	Check if a file pointed by path exists, is a regular file,
**	can be executed by current user. If not it return an error
**	and print error message on stderr.
**
**	return Value:
**		SUCESS : file can be considered as an executable
**		ERROR : file cannot be considered as an executable
*/

int		sh_traverse_sc_check_perm(char *path, char *command_name)
{
	struct stat		st;

	if (stat(path, &st) == -1)
	{
		if (sh_verbose_exec())
			ft_dprintf(2, "%s do not exists\n", path);
		return (sh_perror_err(path, SH_ERR2_NO_SUCH_FILE_OR_DIR));
	}
	if (access(path, X_OK))
	{
		if (sh_verbose_exec())
			ft_dprintf(2, "You do not have execution rights on %s\n", command_name);
		return (sh_perror_err(command_name, SH_ERR1_PERM_DENIED));
	}
	if (!S_ISREG(st.st_mode))
	{
		if (S_ISDIR(st.st_mode))
		return (sh_perror_err("is a directory", path));
		if (sh_verbose_exec())
			ft_dprintf(2, "%s is not a regular file\n", command_name);
		return (sh_perror_err(command_name, SH_ERR1_CMD_NOT_FOUND));
	}
	return (SUCCESS);
}
