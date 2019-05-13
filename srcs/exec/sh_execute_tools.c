/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:34:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/12 15:09:42 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_check_execute:
**	Check if the substituted command path is valid: it exists,
**	it's not a directory, you can execute it
*/

int		sh_check_execute(char *full_path, char *command_name)
{
	struct stat	st;

	if (access(full_path, F_OK))
		return (ft_perror(SH_ERR1_CMD_NOT_FOUND, command_name));
	if (stat(full_path, &st) == -1)
		return (FAILURE);
	if (S_ISDIR(st.st_mode))	//Need to check if it's a normal file instead ??
		return (ft_perror(SH_ERR1_CMD_NOT_FOUND, command_name));
	else if (access(full_path, X_OK))
		return (ft_perror(SH_ERR1_PERM_DENIED, command_name));
	return (SUCCESS);
}
