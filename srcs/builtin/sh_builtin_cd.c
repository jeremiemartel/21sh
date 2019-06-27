/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/27 19:16:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int sh_builtin_cd_rule5(t_context *context, char **curpath, char *param)
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

static int sh_builtin_cd_rule7(t_context *context, char **curpath, char flags)
{
	if (flags == 'L')
	{
		if (**curpath != '/')
		{
			char	*pwd = sh_vars_get_value(context->env, NULL, "PWD");
			if (!pwd)
			{
				free(*curpath);
				return (sh_perror_err_fd(context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "PWD"));
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
		if (find[2] == '/')
			end++;
		if (find - 1 == *curpath)
			start = find;
		else
		{
			find[-1] = 0;
			start = ft_strrchr(*curpath, '/');
		}
		ft_strdelchars(start, 0, end - start);
	}
	while ((find = ft_strnstr(*curpath, ".", 2)))
	{
		if (find[1] == '/')
			ft_strdelchars(find, 0, 2);
		else
			ft_strdelchars(find, 0, 1);
	}
	while ((find = ft_strstr(*curpath, "//")))
		ft_strdelchars(find, 0, 2);
	return (SUCCESS);
	context = NULL;
}

static int		sh_builtin_cd_update_pwd(t_context *context) // Use curdir as pwd??
{
	char		*pwd;
	char		*old_pwd;

	if (!(pwd = getcwd(NULL, CWD_LEN)))
		return (FAILURE); // ?? error message
	if (!(old_pwd = sh_vars_get_value(context->env, NULL, "PWD")))
		old_pwd = pwd;
	if (sh_vars_assign_key_val(context->env, NULL, "OLDPWD", old_pwd) != SUCCESS)
		return (FAILURE);
	if (sh_vars_assign_key_val(context->env, NULL, "PWD", pwd) != SUCCESS)
		return (FAILURE);
	free(pwd);
	return (SUCCESS);
}

int		sh_builtin_cd(t_context *context)
{
	char	*home;
	char	*param;
	char	*curpath;
	char	flags;
	int		i;
	int		ret;

	// parsing : flags, 
	i = 1;
	flags = 'L';
	curpath = NULL;

	home = sh_vars_get_value(context->env, NULL, "HOME");
	param = context->params->tbl[i];
	// rules 1 - 2
	if ((!param || !*param) && (!home || !*home))
		return (sh_perror_err_fd(context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "HOME"));
	else if (!param || !*param)
		curpath = ft_strdup(home);
	// rules 3 - 6
	else if (*param == '/')
	{
		curpath = ft_strdup(param);

	}
	else if (*param == '.' || ft_strnstr(param, "..", 2))
	{
		curpath = ft_strdup(param);
	}
	else
		if ((ret = sh_builtin_cd_rule5(context, &curpath, param)) != SUCCESS)
			return (ret);
	//rule 6 : drop ??

	// ft_dprintf(2, "curpath : %s\n", curpath);

	// if (flags == 'P')
	// 	sh_builtin_cd_rule10(context);

	// rules 7 - 10
	sh_builtin_cd_rule7(context, &curpath, flags);
	sh_builtin_cd_rule8(context, &curpath);
	// rule 9
	// rule 10
	if (curpath)
	{
		chdir(curpath);
		sh_builtin_cd_update_pwd(context);
	}
	free(curpath);
	return (SUCCESS);
}
