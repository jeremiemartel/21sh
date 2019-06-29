/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:05:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/29 14:48:42 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		sh_builtin_pwd_parser(t_context *context, int *i, int *flags)
{
	char	**params;

	params = (char**)context->params->tbl;
	*flags = CD_OPT_LOGIC;
	while (params[*i])
	{
		if (ft_strequ(params[*i], "-P"))
			*flags = CD_OPT_PHYSIC;
		else if (ft_strequ(params[*i], "-L"))
			*flags = CD_OPT_LOGIC;
		else
			return ;
		*i += 1;
	}
	return ;
}

char		*sh_builtin_pwd_physical(int fd_err)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, CWD_LEN)))
		return (sh_perrorn_fd(fd_err, "getcwd(3) error", "sh_builtin_pwd_logical"));
	return (pwd);
}

char		*sh_builtin_pwd_logical(t_dy_tab *env, int fd_err)
{
	char	*pwd;

	pwd = sh_vars_get_value(env, NULL, "PWD");
	if (pwd && *pwd == '/' && !ft_strchr(pwd, '.'))
		return (ft_strdup(pwd));
	else
		return (sh_builtin_pwd_physical(fd_err));
}

int				sh_builtin_pwd(t_context *context)
{
	int		i;
	int		flags;
	char	*pwd;

	i = 1;
	sh_builtin_pwd_parser(context, &i, &flags);

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
