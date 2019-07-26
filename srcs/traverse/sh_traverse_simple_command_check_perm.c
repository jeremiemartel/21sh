/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command_check_perm.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:23:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/26 03:15:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_sc_check_perm_quiet:
**	(Do the same than sh_traverse_sc_check_perm, with no error messages shown)
**	Check if a file pointed by path exists, is a regular file,
**	can be executed by current user. If not it return ERROR.
**	shell->ret_value is not modified.
**
**	return Value:
**		SUCESS : file can be considered as an executable
**		ERROR : file cannot be considered as an executable
*/

int			sh_traverse_sc_check_perm_quiet(char *path)
{
	struct stat	st;

	if (lstat(path, &st) == -1)
		return (ERROR);
	if (stat(path, &st) == -1)
		return (ERROR);
	if (access(path, X_OK))
		return (ERROR);
	if (S_ISDIR(st.st_mode))
		return (ERROR);
	if (!S_ISREG(st.st_mode))
		return (ERROR);
	return (SUCCESS);
}

static int	sh_traverse_sc_check_perm_reg(t_context *context, struct stat st,
			char *command_name)
{
	if (S_ISDIR(st.st_mode))
	{
		sh_env_update_ret_value(context->shell, SH_RET_NOT_EXECUTABLE);
		return (sh_perror(context->params->tbl[0], SH_ERR1_IS_DIR));
	}
	if (sh_verbose_exec())
		ft_dprintf(2, "%s is not a regular file\n", command_name);
	sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
	return (sh_perror_err(command_name, SH_ERR1_CMD_NOT_FOUND));
}

/*
** sh_traverse_sc_check_symlink_loop:
**	Check if file designated by path exists and is not in a symlink loop.
**	If it designate a loop lstat will succeed and stat will fail.
**	If both fail file do not exists.
**	Error messages are written on STDERR.
**
**	Returned Values:
**		SUCCESS : file exists and not in a loop
**		ERROR : file do not exists or is in a loop
*/

static int	sh_traverse_sc_check_symlink_loop(t_context *context, char *path, struct stat *st)
{
	int			ret_stat;
	int			ret_lstat;

	ret_lstat = lstat(path, st);
	ret_stat = stat(path, st);
	if (ret_lstat != -1 && ret_stat == -1)
		return (sh_perror_err(path, SH_ERR2_TOO_MANY_SYMLINK));
	if (ret_stat == -1)
	{
		if (sh_verbose_exec())
			ft_dprintf(2, "%s do not exists\n", path);
		sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
		return (sh_perror_err(path, SH_ERR2_NO_SUCH_FILE_OR_DIR));
	}
	return (SUCCESS);
}

/*
** sh_traverse_sc_check_perm:
**	Check if a file pointed by path exists, is a regular file,
**	can be executed by current user. If not it return an error
**	and print error message on stderr.
**	shell->ret_value is updated if any error occured
**
**	return Value:
**		SUCESS : file can be considered as an executable
**		ERROR : file cannot be considered as an executable
*/

int			sh_traverse_sc_check_perm(t_context *context, char *path,
			char *command_name)
{
	struct stat		st;

	if (sh_traverse_sc_check_symlink_loop(context, path, &st) == ERROR)
		return (ERROR);
	if (access(path, X_OK))
	{
		if (sh_verbose_exec())
			ft_dprintf(2,
			"You do not have execution rights on %s\n", command_name);
		sh_env_update_ret_value(context->shell, SH_RET_NOT_EXECUTABLE);
		return (sh_perror_err(command_name, SH_ERR1_PERM_DENIED));
	}
	if (!S_ISREG(st.st_mode))
		return (sh_traverse_sc_check_perm_reg(context, st, command_name));
	return (SUCCESS);
}
