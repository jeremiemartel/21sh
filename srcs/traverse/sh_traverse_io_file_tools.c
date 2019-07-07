/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:55:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/05 00:45:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	set_failed_command(t_context *context)
{
	context->current_command_node->metadata.command_metadata.should_exec = 0;
}

int		sh_process_file_output(char *filename,
		t_context *context, int options)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (stat(filename, &st) != -1)
	{
		if (S_ISDIR(st.st_mode))
			fd = sh_perror_err(SH_ERR1_IS_DIR, filename);
		else if (access(filename, R_OK))
			fd = sh_perror_err(SH_ERR1_PERM_DENIED, filename);
	}
	if (fd == ERROR)
	{
		set_failed_command(context);
		return (ERROR);
	}
	if ((fd = open(filename, options, 0644)) < 0)
	{
		set_failed_command(context);
		return (sh_perror_err("Can't create file", filename));
	}
	if (sh_add_redirection(sh_new_redir(OUTPUT, context->redirected_fd, fd),
		&context->current_command_node->metadata.command_metadata.redirections))
		return (FAILURE);
	return (SUCCESS);
}

int		sh_process_file_input(char *filename,
		t_context *context, int options)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (access(filename, F_OK))
		fd = sh_perror(SH_ERR2_NO_SUCH_FILE_OR_DIR, filename);
	if (stat(filename, &st) == -1)
	{
		set_failed_command(context);
		return (ERROR);
	}
	else if (access(filename, R_OK))
		fd = sh_perror_err(SH_ERR1_PERM_DENIED, filename);
	if (fd == ERROR)
	{
		set_failed_command(context);
		return (ERROR);
	}
	if ((fd = open(filename, options)) < 0)
		return (sh_perror("Can't open file", filename));
	if (sh_add_redirection(sh_new_redir(INPUT, context->redirected_fd, fd),
		&context->current_command_node->metadata.command_metadata.redirections))
		return (FAILURE);
	return (SUCCESS);
}
