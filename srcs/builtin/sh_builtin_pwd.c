/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:05:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/15 16:47:13 by ldedier          ###   ########.fr       */
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

	pwd = sh_builtin_pwd_tool(context->env);
	if (!pwd)
		return (FAILURE);
	ft_dprintf(context->fd[FD_OUT], "%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
