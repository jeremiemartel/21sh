/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:48:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/17 11:36:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		end_with_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (--i >= 0 && str[i] == c)
		return (FAILURE);
	return (SUCCESS);
}

char	*get_path_from_request(char *old_pwd, char *path)
{
	if (path[0] == '/')
		return (get_sanitized_path_from_old("/", &(path[1])));
	else
		return (get_sanitized_path_from_old(old_pwd, path));
}

int		ft_update_old_pwd(char *old_pwd, char *path, t_cd_opt flag,
			t_context *context)
{
	char		cwd[CWD_LEN];
	char		*pwd_value;
	char		*final_pwd;

	if (!getcwd(cwd, CWD_LEN))
		return (FAILURE);
	if (flag == e_cd_opt_physic)
		final_pwd = ft_strdup(cwd);
	else
		final_pwd = get_path_from_request(old_pwd, path);
	if (!final_pwd)
		return (FAILURE);
	if (!(pwd_value = get_env_value((char **)context->env->tbl, "PWD")))
		sh_vars_assign_key_val(context->env, NULL, "OLDPWD", old_pwd);
	else
		sh_vars_assign_key_val(context->env, NULL, "OLDPWD", pwd_value);
	sh_vars_assign_key_val(context->env, NULL, "PWD", final_pwd);
	free(final_pwd);
	return (SUCCESS);
}
