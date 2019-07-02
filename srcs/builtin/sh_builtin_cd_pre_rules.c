/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_pre_rules.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:50:45 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/01 15:20:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_cd_parser_hyphen(
	t_context *context, char *flag, char **curpath)
{
	char	*oldpwd;

	if (!(oldpwd = sh_vars_get_value(context->env, NULL, "OLDPWD")))
		return (sh_perror_err_fd(
			context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "OLDPWD"));
	if (!(*curpath  = ft_strdup(oldpwd)))
		return (sh_perror_fd(
			context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_parser"));
	*flag += CD_OPT_HYPHEN;
	return (SUCCESS);
}

int	sh_builtin_cd_parser(t_context *context, int *i, char *flag, char **curpath)
{
	char	**params;

	params = (char**)context->params->tbl;
	*flag = CD_OPT_LOGIC;
	while (params[*i])
	{
		if (ft_strequ(params[*i], "-P"))
			*flag = CD_OPT_PHYSIC;
		else if (ft_strequ(params[*i], "-L"))
			*flag = CD_OPT_LOGIC;
		else if (ft_strequ(params[*i], "-"))
			return (sh_builtin_cd_parser_hyphen(context, flag, curpath));
		else
			return (SUCCESS);
		*i += 1;
	}
	return (SUCCESS);
}

int	sh_builtin_cd_pre_rules(t_context *context, char *param, char **curpath)
{
	char	*home;
	int		ret;

	home = sh_vars_get_value(context->env, NULL, "HOME");
	// rules 1 - 2
	if (*curpath)
		;
	else if ((!param || !*param) && (!home || !*home))
		return (sh_perror_err_fd(context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "HOME"));
	else if (!param || !*param)
		*curpath = ft_strdup(home);
	// rules 3 - 6
	else if (*param == '/')
		*curpath = ft_strdup(param);
	else if (*param == '.' || ft_strnstr(param, "..", 2))
		*curpath = ft_strdup(param);
	else
	{
		if ((ret = sh_builtin_cd_rule5(context, curpath, param)) != SUCCESS)
			return (ret);
	}
	if (!*curpath)
		return (sh_perror_fd(
			context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_pre_rules"));
	return (SUCCESS);
}

int	sh_builtin_cd_rule5(t_context *context, char **curpath, char *param)
{
	char	*cdpath;

	cdpath = sh_vars_get_value(context->env, NULL, "CDPATH");
	if (!cdpath || !*cdpath)
	{
		*curpath = ft_strjoin_path(".", param);
		if (!curpath)
			return (sh_perror_fd(
				context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_rule5"));
		return (SUCCESS);
	}
	return (ERROR); // need to implement CDPATH
}
