/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:34:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/20 17:16:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_check_execute(char *full_path, char *command_name)
{
	struct stat	st;

	if (access(full_path, F_OK))
	{
		ft_dprintf(2, "21sh: %s: command not found\n", command_name);
		return (1);
	}
	else
	{
		if (stat(full_path, &st) == -1)
			return (-1);
		if (S_ISDIR(st.st_mode))
		{
			ft_dprintf(2, "21sh: %s: command not found\n", command_name);
			return (1);
		}
		else if (access(full_path, X_OK))
			return (ft_perror(SH_ERR1_PERM_DENIED, command_name));
	}
	return (0);
}