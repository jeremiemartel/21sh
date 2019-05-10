/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:05:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 19:00:51 by ldedier          ###   ########.fr       */
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
	int		i;

	i = 0;
	while (context->params->tbl[i])
	{
		if (context->params->tbl[++i] && *(char**)context->params->tbl[i])
		{
			ft_perror("pwd", SH_ERR1_TOO_MANY_ARGS);
			return (1);
		}
	}
	pwd = sh_builtin_pwd_tool(context->env);
	if (!pwd)
		return (FAILURE);
	ft_putstrn(pwd);
	free(pwd);
	return (SUCCESS);
}
