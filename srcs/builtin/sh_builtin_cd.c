/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/29 15:11:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_cd_parser(t_context *context, int *i, char *flags, char **curpath)
{
	char	**params;
	char	*oldpwd;

	params = (char**)context->params->tbl;
	*flags = CD_OPT_LOGIC;
	while (params[*i])
	{
		if (ft_strequ(params[*i], "-P"))
			*flags = CD_OPT_PHYSIC;
		else if (ft_strequ(params[*i], "-L"))
			*flags = CD_OPT_LOGIC;
		else if (ft_strequ(params[*i], "-"))
		{
			if (!(oldpwd = sh_vars_get_value(context->env, NULL, "OLDPWD")))// || !*oldpwd)
				return (sh_perror_err_fd(context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "OLDPWD"));
			if (!(*curpath  = ft_strdup(oldpwd)))
				return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_parser"));
			*flags += CD_OPT_HYPHEN;
			return (SUCCESS);
		}
		else
			return (SUCCESS);
		*i += 1;
	}
	return (SUCCESS);
}

static int	sh_builtin_cd_rule5(t_context *context, char **curpath, char *param)
{
	char	*cdpath;

	cdpath = sh_vars_get_value(context->env, NULL, "CDPATH");
	if (!cdpath)
	{
		*curpath = ft_strjoin_path(".", param); // protect malloc
		if (!curpath)
			return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_rule5"));
		return (SUCCESS);
	}
	return (ERROR); // need to implement CDPATH
}

static int		sh_builtin_cd_pre_rules(t_context *context, char *param, char **curpath)
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
		return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_pre_rules"));
	return (SUCCESS);
}

static int	sh_builtin_cd_rule7(t_context *context, char **curpath, char flags)
{
	char	*pwd;

	if (flags & CD_OPT_LOGIC)
	{
		if (**curpath != '/')
		{
			pwd = sh_builtin_pwd_logical(context->env, context->fd[FD_ERR]);
			if (!pwd)
			{
				free(*curpath);
				return (ERROR);
			}
			*curpath = ft_strjoin_path(pwd, *curpath); // free curpath and protect mallocs
		}
	}
	// else
		// sh_builtin_cd_rule10(context, &curpath);
	return (SUCCESS);
}

static int sh_builtin_cd_rule8(t_context *context, char **curpath)
{
	char	*find;
	char	*end;
	char	*start;

	while ((find = ft_strstr(*curpath, "..")))
	{
		end = find + 2;
		// if (find[2] == '/')
		// 	end++;
		if (find == *curpath || find - 1 == *curpath) // ..* or /..* conf
			start = find;
		else
		{
			find[-1] = 0;
			start = ft_strrchr(*curpath, '/');
			find[-1] = '/';
			if (start == *curpath)
				start++;
		}
		// ft_dprintf(2, "start : %.5s | end : %.5s\n", start, end - 5);
		// ft_dprintf(2, "before : %s", *curpath);
		// ft_dprintf(2, "to delete : %*s | len : %d\n", end - start, start, end - start);
		ft_strdelchars(start, 0, end - start);
		// ft_dprintf(2, " | after : %s\n", *curpath);
		// ft_dprintf(2, " | after : start :  %s\n", start);
	}

	while ((find = ft_strstr(*curpath, ".")))
	{
		if (find[1] == '/')
			ft_strdelchars(find, 0, 2);
		else
			ft_strdelchars(find, 0, 1);
	}
	while ((find = ft_strstr(*curpath, "//")))
		ft_strdelchars(find, 0, 1);
	int		len;

	len = ft_strlen(*curpath);
	if (len > 1 && (*curpath)[len - 1] == '/')
		(*curpath)[len - 1] = '\0';
	return (SUCCESS);
	context = NULL;
}

static int		sh_builtin_cd_update_pwd(t_context *context, int flags, char *curpath) // Use curdir as pwd??
{
	char		*pwd;
	char		*old_pwd;

	if (flags & CD_OPT_LOGIC)
		pwd = curpath;
	else
		pwd = sh_builtin_pwd_physical(context->fd[FD_ERR]);
	if (!pwd)
		return (ERROR);
	old_pwd = sh_vars_get_value(context->env, NULL, "PWD");
	if (old_pwd)
		if (sh_vars_assign_key_val(context->env, NULL, "OLDPWD", old_pwd) != SUCCESS)
			return (FAILURE);
	if (sh_vars_assign_key_val(context->env, NULL, "PWD", pwd) != SUCCESS)
		return (FAILURE);
	// free(pwd);
	return (SUCCESS);
	flags = 0;
}

static int sh_builtin_cd_rule10(t_context *context, char *curpath, int flags, char *param)
{
	int		ret;

	ret = SUCCESS;
	if (curpath && *curpath)
	{
		struct stat		st;

		// ft_dprintf(2, "check permisions on : %s\n", curpath);
		if (access(curpath, F_OK))
			ret = sh_perror_err_fd(context->fd[FD_ERR], param, SH_ERR2_NO_SUCH_FILE_OR_DIR);
		else if (stat(curpath, &st) == -1)
			ret = sh_perror_err_fd(context->fd[FD_ERR], param, SH_ERR2_NO_SUCH_FILE_OR_DIR);
		else if (!S_ISDIR(st.st_mode))
			ret = sh_perror2_err_fd(context->fd[FD_ERR], SH_ERR1_NOT_A_DIR, "cd", param);
		else if (access(curpath, X_OK))
			ret = sh_perror2_err_fd(context->fd[FD_ERR], SH_ERR1_PERM_DENIED, "cd", param);
	}
	if (!ret && curpath && *curpath)
		chdir(curpath);
	if (!ret)
		sh_builtin_cd_update_pwd(context, flags, curpath);
	if (flags & CD_OPT_HYPHEN)
	{
		ft_dprintf(context->fd[FD_OUT], "%s\n", sh_vars_get_value(context->env, NULL, "PWD"));
		// ft_dprintf(2, "%s\n", sh_vars_get_value(context->env, NULL, "PWD")); // change 2 !!
	}
	return (ret);
	
}

int		sh_builtin_cd(t_context *context)
{
	char	*param;
	char	*curpath;
	char	flags;
	int		i;
	int		ret;

	i = 1;
	curpath = NULL;
	if ((ret = sh_builtin_cd_parser(context, &i, &flags, &curpath)))
		return (ret);
	param = context->params->tbl[i];
	if ((ret = sh_builtin_cd_pre_rules(context, param, &curpath)))
		return (ret);
	if (ft_strequ(param, "-"))
		param[0] = 0;
	// ft_dprintf(2, "before post rules curpath : %s\n", curpath);
	// rule 7
	if (!(flags & CD_OPT_PHYSIC))
	{
		sh_builtin_cd_rule7(context, &curpath, flags);
		sh_builtin_cd_rule8(context, &curpath);
	}
	ret = sh_builtin_cd_rule10(context, curpath, flags, param);
	free(curpath);
	return (ret);
}
