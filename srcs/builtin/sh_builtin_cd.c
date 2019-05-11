/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/11 18:37:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		ft_print_cd_errors(char *path)
{
	struct stat st;

	if (access(path, F_OK))
		ft_dprintf(2, "%s: cd: %s: Not such file or directory\n",
				SH_NAME, path);
	else
	{
		if (stat(path, &st) == -1)
			return (-1);
		else
		{
			if (!S_ISDIR(st.st_mode))
				ft_dprintf(2, "%s: cd: %s: Not a directory\n", SH_NAME, path);
			else if (access(path, X_OK))
				ft_dprintf(2, "%s: cd: %s: Permission denied\n", SH_NAME, path);
		}
	}
	return (1);
}

int		ft_process_cd(char *path, t_cd_opt flag, t_context *context)
{
	char		old_pwd[CWD_LEN];

	if (!getcwd(old_pwd, CWD_LEN))
		return (-1);
	if (chdir(path) != 0)
		return (ft_print_cd_errors(path));
	else if (ft_update_old_pwd(old_pwd, path, flag, context) == -1)
		return (-1);
	return (1);
}

int		ft_process_cd_args(t_context *context, int flag, int i)
{
	char	**tmp;
	char	*str;

	if (!ft_strcmp("-", context->params->tbl[i]))
	{
		if ((str = get_env_value((char **)context->env->tbl, "OLDPWD")))
		{
			ft_process_cd(str, flag, context);
			tmp = (char **)context->params->tbl;
			if (!(context->params->tbl = (void **)ft_strsplit("pwd", ' ')))
				return (-1);
			ft_strtab_free(tmp);
			return (sh_execute_command(context) == -1 ? -1 : 1);
		}
		else
		{
			ft_dprintf(2, "%s: cd: OLDPWD not set\n", SH_NAME);
			return (1);
		}
	}
	else
		return (ft_process_cd(context->params->tbl[i], flag, context));
}

int		sh_builtin_cd(t_context *context)
{
	char	*home_str;
	int		i;
	int		flag;
	int		ret;

	flag = e_cd_opt_logic;
	i = 1;
	while (context->params->tbl[i])
	{
		if (!ft_strcmp(context->params->tbl[i], "-P"))
			flag = e_cd_opt_physic;
		else if (!ft_strcmp(context->params->tbl[i], "-L"))
			flag = e_cd_opt_logic;
		else if ((ret = ft_process_cd_args(context, flag, i)))
			return (ret);
		i++;
	}
	if ((home_str = get_env_value((char **)context->env->tbl, "HOME")))
		return (ft_process_cd(home_str, flag, context));
	else
	{
		ft_dprintf(2, "%s: cd: HOME not set\n", SH_NAME);
		return (1);
	}
	return (1);
}
