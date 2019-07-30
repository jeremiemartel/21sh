/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_clipboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 23:50:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/30 14:55:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*refined_str(char *str)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(str);
	if (!(res = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (ft_isascii(str[i]))
			res[i] = str[i];
		else
			res[i] = '?';
		i++;
	}
	res[i] = '\0';
	return (res);
}

int		process_clipboard_line_nl(t_shell *shell, t_command_line *command_line,
			char *str)
{
	if (paste_current_index(command_line, str))
	{
		free(str);
		return (FAILURE);
	}
	process_enter_no_autocompletion(command_line);
	if (sh_process_received_command(shell, command_line) == FAILURE)
	{
		free(str);
		return (FAILURE);
	}
	if (reset_command_line(shell, command_line) == FAILURE)
	{
		free(str);
		return (FAILURE);
	}
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}

int		process_clipboard_line(t_shell *shell, t_command_line *command_line,
			t_gnl_info *info)
{
	char *ref;

	if (!(ref = refined_str(info->line)))
	{
		return (FAILURE);
		free(info->line);
	}
	free(info->line);
	if (info->separator == '\n')
	{
		if (process_clipboard_line_nl(shell, command_line, ref))
			return (FAILURE);
	}
	else if (info->separator == '\0')
	{
		free(ref);
		return (sh_perror(SH_ERR1_UNEXPECTED_EOF, "process_clipboard_from_fd"));
	}
	else if (paste_current_index(command_line, ref))
	{
		free(ref);
		return (FAILURE);
	}
	free(ref);
	return (SUCCESS);
}

int		process_clipboard_from_fd(
	t_shell *shell, int fd, t_command_line *command_line)
{
	t_gnl_info	info;
	int			ret;

	while ((ret = get_next_line2(fd, &info, BUFF_SIZE)) > 0)
	{
		if (process_clipboard_line(shell, command_line, &info))
			return (FAILURE);
	}
	if (ret == -1)
		return (sh_perror(SH_ERR1_MALLOC, "process_clipboard_from_fd"));
	free(info.line);
	return (SUCCESS);
}

int		process_clipboard_son(int fds[2], char *pbpaste_path)
{
	char	**split;

	close(fds[PIPE_OUT]);
	dup2(fds[PIPE_IN], 1);
	if (!(split = ft_strsplit(pbpaste_path, ' ')))
		return (1);
	if (execve(pbpaste_path, split, NULL) == -1)
	{
		ft_strtab_free(split);
		return (1);
	}
	return (1);
}

int		process_clipboard_shell(t_shell *shell, t_command_line *command_line)
{
	int		pid;
	int		fds[2];
	int		ret;

	if (pipe(fds))
		return (sh_perror(SH_ERR1_PIPE, "proces_clipboard_shell"));
	if ((pid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "proces_clipboard_shell"));
	if (pid == 0)
		exit(process_clipboard_son(fds, "/usr/bin/pbpaste"));
	else
	{
		close(fds[PIPE_IN]);
		wait(&ret);
		if (ret)
			return (sh_perror(SH_ERR1_PBPASTE, "process_clipboard"));
		return (process_clipboard_from_fd(shell, fds[PIPE_OUT], command_line));
	}
}
