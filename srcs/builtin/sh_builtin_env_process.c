/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:31:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/06 19:36:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_env_no_args:
**	Print current environment on stdout, used when env is called with no args.
**
**	return SUCCESS
*/

int			sh_builtin_env_no_args(t_context *context)
{
	size_t		i;
	t_dy_tab	*env;

	env = context->env;
	i = 0;
	while (i < env->current_size)
	{
		ft_dprintf(context->fd[FD_OUT], "%s\n", env->tbl[i]);
		i++;
	}
	return (SUCCESS);
}

/*
** sh_builtin_env_process_no_slash:
**	Function launching the execution of a process if command to invoke
**	do not contain a path (does not contain a '/' character).
**	It try to launch any builtin, then look in $PATH env variable.
**	If any command was found it is launched.
**	Before launching any valid builtin or command context->env is set
**	to new_env;
**	(Final else return SUCCESS to let cmd || cmd works)
**
** returned Values :
**	FAILURE : malloc error
**	ERROR : command not found
**	Else :	any value returned by a builtin executed or a process launched
*/

static int	sh_builtin_env_process_no_slash
	(t_context *context, t_dy_tab *new_env)
{
	if ((context->builtin = sh_builtin_find(context)))
	{
		context->env = new_env;
		return (sh_exec_builtin(context));
	}
	if (sh_traverse_sc_search_in_hash(context) != SUCCESS)
	{
		if (sh_traverse_sc_search_in_path(context) == FAILURE)
			return (FAILURE);
	}
	if (context->path)
	{
		context->env = new_env;
		if (context->current_pipe_sequence_node)
		{
			execve(context->path,
			(char**)context->params->tbl, (char**)context->env->tbl);
			sh_perror(((char**)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
			return (SH_RET_NOT_EXECUTABLE);
		}
		else
			return (sh_process_execute(context));
	}
	sh_perror_err(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
	sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
	return (SUCCESS);
}

/*
** sh_builtin_env_process_slash:
**	Function launching the execution of a process if command to invoke
**	contain a path (contain a '/' character).
**	If path correspond to any valid file (exits, regular executable file)
**	Before launching any valid command context->env is set to new_env;
**
** returned Values :
**	FAILURE : malloc error
**	ERROR : command not found
**	Else :	any value returned by the process launched
*/

static int	sh_builtin_env_process_slash(t_context *context, t_dy_tab *new_env)
{
	int			ret;
	t_dy_tab	*save_env;

	if (!(context->path = ft_strdup(context->params->tbl[0])))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_env_process_command"));
	if (sh_traverse_sc_check_perm(context, context->path,
		context->params->tbl[0]) == ERROR)
		ret = ERROR;
	else
	{
		save_env = context->env;
		context->env = new_env;
		if (context->current_pipe_sequence_node)
		{
			execve(context->path,
			(char**)context->params->tbl, (char**)context->env->tbl);
			sh_perror(((char**)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
			ret = SH_RET_NOT_EXECUTABLE;
		}
		else
			ret = sh_process_execute(context);
		context->env = save_env;
	}
	return (ret);
}

/*
** sh_builtin_env_process_command:
**	Categorize given command as path or a command, and call concerned functions
**
** returned Values:
**	FAILURE : malloc error
**	ERROR : command not found
**	Else :	any value returned by a builtin executed or a process launched
*/

int			sh_builtin_env_process_command
	(t_context *context, t_dy_tab *new_env)
{
	int			ret;

	if (!context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_builtin_env_process_no_slash(context, new_env);
	else
		ret = sh_builtin_env_process_slash(context, new_env);
	return (ret);
}
