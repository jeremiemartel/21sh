/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:05:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/30 15:18:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_pwd_usage:
**		Print pwd usage on fdout.
*/

static void	sh_builtin_pwd_usage(int fdout)
{
	sh_perror_fd(fdout, "usage: pwd [-LP]", "pwd");
	return ;
}

/*
** sh_builtin_pwd_parser:
**	Read in command parameters to select between -P and -L options.
**	The last one found is used. If no one is specified -L is used.
**
**	returned Values :
**		ERROR : Invalid option given
**		SUCCESS : Successfully detected options
*/

static int	sh_builtin_pwd_parser(t_context *context, int *i, int *flags)
{
	char	**params;

	params = (char**)context->params->tbl;
	*flags = CD_OPT_LOGIC;
	while (params[*i] && params[*i][0] == '-')
	{
		if (ft_strequ(params[*i], "-P"))
			*flags = CD_OPT_PHYSIC;
		else if (ft_strequ(params[*i], "-L"))
			*flags = CD_OPT_LOGIC;
		else
		{
			sh_perror2_err_fd(
				context->fd[FD_ERR], SH_ERR2_INVALID_OPT, "pwd", params[*i]);
			sh_builtin_pwd_usage(context->fd[FD_ERR]);
			return (ERROR);
		}
		*i += 1;
	}
	return (SUCCESS);
}

/*
** sh_builtin_pwd_physical:
**	Return an absolute pathname, that do not contain any symlinks.
**
**	returned Values :
**		NULL : Malloc error
**		Else : New malloced string, containing path
*/

char		*sh_builtin_pwd_physical(int fd_err)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, CWD_LEN)))
	{
		sh_perrorn_fd(fd_err, "getcwd(3) error", "sh_builtin_pwd_logical");
		return (NULL);
	}
	return (pwd);
}

/*
** sh_builtin_pwd_logical:
**	Return an absolute pathname, not containing any dot or dot-dot.
**	Symlinks may appear in the path.
**
**	returned Values :
**		NULL : Malloc error
**		Else : New malloced string, containing path
*/

char		*sh_builtin_pwd_logical(t_dy_tab *env, int fd_err)
{
	char	*pwd;

	pwd = sh_vars_get_value(env, NULL, "PWD");
	if (pwd && *pwd == '/' && !ft_strchr(pwd, '.'))
		return (ft_strdup(pwd));
	else
		return (sh_builtin_pwd_physical(fd_err));
}

/*
** sh_builtin_pwd:
**	Function called as the pwd builtin. First options are parsed,
**	Then it use the pwd "api" to get the path, depending on given options.
**
**	returned Values :
**		FAILURE : malloc error
**		ERROR : invalid option detected (print usage)
**		SUCCESS : Path had been printed
*/

int			sh_builtin_pwd(t_context *context)
{
	int		i;
	int		flags;
	char	*pwd;

	i = 1;
	if (sh_builtin_pwd_parser(context, &i, &flags) != SUCCESS)
		return (ERROR);
	if (flags & CD_OPT_LOGIC)
		pwd = sh_builtin_pwd_logical(context->env, context->fd[FD_ERR]);
	else
		pwd = sh_builtin_pwd_physical(context->fd[FD_ERR]);
	if (!pwd)
		return (FAILURE);
	ft_dprintf(context->fd[FD_OUT], "%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
