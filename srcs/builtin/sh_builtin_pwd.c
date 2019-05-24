/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:05:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/24 15:51:22 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char		*sh_builtin_pwd_tool(t_dy_tab *env)
{
	char	*pwd;
	char	buf[__DARWIN_MAXPATHLEN];

	if ((pwd = sh_vars_get_value(env, NULL, "PWD")) && *pwd)
		return (ft_strdup(pwd));
	if (!getcwd(buf, __DARWIN_MAXPATHLEN))
		return (NULL);
	else
		return (ft_strdup(buf));
}

int				sh_builtin_pwd(t_context *context)
{
	char	*pwd;

	// Commented to be used in "cd -" command
	// if (context->params->tbl[1])
	// 	return (ft_perror("pwd", SH_ERR1_TOO_MANY_ARGS)); 
	pwd = sh_builtin_pwd_tool(context->env);
	if (!pwd)
		return (FAILURE);
	ft_dprintf(context->fd[FD_OUT], "%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
