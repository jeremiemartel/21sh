/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_post_rules.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:33:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 13:37:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	sh_builtin_cd_rule7(t_context *context, char **curpath, char flags)
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
			free(*curpath);
			if (!(*curpath = ft_strjoin_path(pwd, *curpath)))
				return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_rule7"));
		}
	}
	return (SUCCESS);
}

static int	sh_builtin_cd_rule8_2(char **curpath)
{
	int		len;
	char	*find;

	while ((find = ft_strstr(*curpath, ".")))
	{
		if (find[1] == '/')
			ft_strdelchars(find, 0, 2);
		else
			ft_strdelchars(find, 0, 1);
	}
	while ((find = ft_strstr(*curpath, "//")))
		ft_strdelchars(find, 0, 1);
	len = ft_strlen(*curpath);
	if (len > 1 && (*curpath)[len - 1] == '/')
		(*curpath)[len - 1] = '\0';
	return (SUCCESS);
}

int	sh_builtin_cd_rule8_1(char **curpath)
{
	char	*find;
	char	*end;
	char	*start;

	while ((find = ft_strstr(*curpath, "..")))
	{
		end = find + 2;
		if (find == *curpath || find - 1 == *curpath)
			start = find;
		else
		{
			find[-1] = 0;
			start = ft_strrchr(*curpath, '/');
			find[-1] = '/';
			if (start == *curpath)
				start++;
		}
		ft_strdelchars(start, 0, end - start);
	}
	return (sh_builtin_cd_rule8_2(curpath));
}

int	sh_builtin_cd_rule10(t_context *context, char *curpath, int flags, char *param)
{
	int			ret;
	struct stat	st;

	ret = SUCCESS;
	if (curpath && *curpath)
	{
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
		ft_dprintf(context->fd[FD_OUT], "%s\n", sh_vars_get_value(context->env, NULL, "PWD"));
	return (ret);
	
}
