/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command_check_perm.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:23:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/05 01:24:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_traverse_sc_check_perm_reg(t_context *context, struct stat st,
			char *command_name)
{
	if (S_ISDIR(st.st_mode))
		return (ERROR);
	if (sh_verbose_exec())
		ft_dprintf(2, "%s is not a regular file\n", command_name);
	sh_env_vars_update_question_mark(context, SH_RET_CMD_NOT_FOUND);
	return (sh_perror_err(command_name, SH_ERR1_CMD_NOT_FOUND));
}

/*
** sh_traverse_sc_check_perm:
**	Check if a file pointed by path exists, is a regular file,
**	can be executed by current user. If not it return an error
**	and print error message on stderr.
**
**	return Value:
**		SUCESS : file can be considered as an executable
**		ERROR : file cannot be considered as an executable
*/

int			sh_traverse_sc_check_perm(t_context *context, char *path,
			char *command_name)
{
	struct stat		st;

	if (stat(path, &st) == -1)
	{
		if (sh_verbose_exec())
			ft_dprintf(2, "%s do not exists\n", path);
		return (sh_perror_err(path, SH_ERR2_NO_SUCH_FILE_OR_DIR));
	}
	if (access(path, X_OK))
	{
		if (sh_verbose_exec())
			ft_dprintf(2,
			"You do not have execution rights on %s\n", command_name);
		sh_env_vars_update_question_mark(context, SH_RET_PERM_DENIED);
		return (sh_perror_err(command_name, SH_ERR1_PERM_DENIED));
	}
	if (!S_ISREG(st.st_mode))
		return (sh_traverse_sc_check_perm_reg(context, st, command_name));
	return (SUCCESS);
}
