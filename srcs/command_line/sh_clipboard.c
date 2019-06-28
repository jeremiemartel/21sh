/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_clipboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 23:50:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/27 23:50:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_clipboard_line_nl(t_shell *shell, t_command_line *command_line,
			t_gnl_info *info)
{
	if (paste_current_index(command_line, info->line))
	{
		free(info->line);
		return (FAILURE);
	}
	process_enter_no_autocompletion(command_line);
	if (sh_process_received_command(shell, command_line)
			&& shell->running == 0)
	{
		free(info->line);
		return (FAILURE);
	}
	if (reset_command_line(shell, command_line) == FAILURE)
	{
		free(info->line);
		return (FAILURE);
	}
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}

int		process_clipboard_line(t_shell *shell, t_command_line *command_line,
			t_gnl_info *info)
{
	if (info->separator == '\n')
	{
		if (process_clipboard_line_nl(shell, command_line, info))
			return (FAILURE);
	}
	else if (info->separator == '\0')
	{
		free(info->line);
		return (sh_perror(SH_ERR1_UNEXPECTED_EOF,
					"process_clipboard_from_fd"));
	}
	else if (paste_current_index(command_line, info->line))
	{
		free(info->line);
		return (FAILURE);
	}
	free(info->line);
	return (SUCCESS);
}

int		process_clipboard_from_fd(t_shell *shell, int fd, t_command_line *command_line)
{
	t_gnl_info	info;
	int			ret;

	while ((ret = get_next_line2(fd, &info)) > 0)
	{
		if (process_clipboard_line(shell, command_line, &info))
			return (FAILURE);
	}
	if (ret == -1)
		return (sh_perror(SH_ERR1_MALLOC, "process_clipboard_from_fd"));
	free(info.line);
	return (SUCCESS);
}

int 	process_clipboard(t_shell *shell, t_command_line *command_line,
			char *pbpaste_path)
{
	int		pid;
	int		fds[2];
	char	**split;

	if (pipe(fds))
		return (1);
	if ((pid = fork()) == -1)
		return (1);
	if (pid == 0)
	{
		close(fds[PIPE_OUT]);
		dup2(fds[PIPE_IN], 1);
		if (!(split = ft_strsplit(pbpaste_path, ' ')))
			return (1);
		execve(pbpaste_path, split, NULL);
		return (1);
	}
	else
	{
		close(fds[PIPE_IN]);
		wait(NULL);
		return (process_clipboard_from_fd(shell, fds[PIPE_OUT], command_line));
	}
}
int		process_clipboard_shell(t_shell *shell, t_command_line *command_line)
{
	(void)shell;
	return (process_clipboard(shell, command_line, "/usr/bin/pbpaste"));
}
