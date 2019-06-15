/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/15 17:19:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		ft_print_cd_errors(char *path, t_context *context)
{
	struct stat st;

	if (access(path, F_OK))
		sh_perror2_fd(context->fd[FD_ERR],
			SH_ERR2_NO_SUCH_FILE_OR_DIR, "cd", path);
	else
	{
		if (stat(path, &st) == -1)
			return (FAILURE);
		else
		{
			if (!S_ISDIR(st.st_mode))
				sh_perror2_fd(context->fd[FD_ERR],
					SH_ERR1_NOT_A_DIR, "cd", path);
			else if (access(path, X_OK))
				sh_perror2_fd(context->fd[FD_ERR],
					SH_ERR1_PERM_DENIED, "cd", path);
		}
	}
	return (SUCCESS);
}

int				ft_process_cd(char *path, t_cd_opt flag, t_context *context)
{
	char		old_pwd[CWD_LEN];

	if (!getcwd(old_pwd, CWD_LEN))
		return (FAILURE);
	if (chdir(path) != 0)
		return (ft_print_cd_errors(path, context));
	else if (ft_update_old_pwd(old_pwd, path, flag, context) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int				ft_process_cd_args(t_context *context, int flag, int i)
{
	char	*str;

	if (!ft_strcmp("-", context->params->tbl[i]))
	{
		if ((str = get_env_value((char **)context->env->tbl, "OLDPWD")))
		{
			if (ft_process_cd(str, flag, context) == FAILURE)
				return (FAILURE);
			return (sh_builtin_pwd(context));
		}
		else
			return (sh_perror2_fd(context->fd[FD_ERR],
				SH_ERR1_ENV_NOT_SET, "cd", "OLDPWD"));
	}
	else
		return (ft_process_cd(context->params->tbl[i], flag, context));
}

int				sh_builtin_cd(t_context *context)
{
	char	*home_str;
	int		i;
	int		flag;

	flag = e_cd_opt_logic;
	i = 1;
	while (context->params->tbl[i])
	{
		if (!ft_strcmp(context->params->tbl[i], "-P"))
			flag = e_cd_opt_physic;
		else if (!ft_strcmp(context->params->tbl[i], "-L"))
			flag = e_cd_opt_logic;
		else
			return (ft_process_cd_args(context, flag, i));
		i++;
	}
	if ((home_str = get_env_value((char **)context->env->tbl, "HOME")))
		return (ft_process_cd(home_str, flag, context));
	else
	{
		return (sh_perror2_fd(context->fd[FD_ERR],
				SH_ERR1_ENV_NOT_SET, "cd", "HOME"));
	}
	return (SUCCESS);
}
