/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:34:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 19:36:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		execute_command_2(t_shell *shell, char *path_str)
{
	int		ret;

	if (path_str)
	{
		if ((ret = execute_command_path(shell, path_str)) != 2)
			return (ret);
	}
	return (execute_command_no_path(shell));
}

int		check_execute(char *full_path, char **params)
{
	struct stat	st;

	if (access(full_path, F_OK))
	{
		ft_dprintf(2, "minishell: %s: command not found\n", params[0]);
		return (1);
	}
	else
	{
		if (stat(full_path, &st) == -1)
			return (-1);
		if (S_ISDIR(st.st_mode))
		{
			ft_dprintf(2, "minishell: %s: command not found\n", params[0]);
			return (1);
		}
		else if (access(full_path, X_OK))
		{
			ft_dprintf(2, "minishell: permission denied: %s\n", shell->params[0]);
			return (1);
		}
	}
	return (0);
}
