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

char	*ft_strjoin_free_clipboard(char *str, char *to_join)
{
	char	*res;
	int		j;
	int		i;
	int		len;

	len = ft_strlen(str);
	if (!(res = ft_strnew(len + ft_strlen(to_join) + 1)))
		return (0);
	ft_strcpy(res, str);
	i = len;
	j = 0;
	while (to_join[j])
	{
		if (ft_isseparator(to_join[i]) && to_join[i] != '\n')
			to_join[j] = ' ';
		res[i] = to_join[j];
		j++;
		i++;
	}
	free(str);
	return (res);
}

char	*get_string_from_fd(int fd)
{
	int ret;
	char *res;
	char buffer[4096 + 1];
	
	if (!(res = ft_strnew(0)))
		return (NULL);
	while ((ret = read(fd, buffer, 4096)) > 0)
	{
		buffer[ret] = '\0';
		if (!(res = ft_strjoin_free_clipboard(res, buffer)))
			return (NULL);
	}
	return (res);
}

int		process_clipboard_from_fd(t_shell *shell, int fd, t_command_line *command_line)
{
	t_gnl_info	info;
	int			ret;

	if (command_line->dy_str->current_size > 0)
	{

	}
	while ((ret = get_next_line2(fd, &info)) > 0)
	{
		if (info.separator == '\n')
		{
			if (add_to_command_line(command_line, info.line))
			{
				free(info.line);
				return (1);
			}
			free(info.line);
			process_enter_no_autocompletion(command_line);
			if (sh_process_received_command(shell, command_line)
					&& shell->running == 0)
				return (1);
			if (reset_command_line(shell, command_line) == FAILURE)
				return (FAILURE);
			render_command_line(command_line, 0, 1);
		}
		else
		{
			if (add_to_command_line(command_line, info.line))
			{
				free(info.line);
				return (1);
			}
		}
	}
	free(info.line);
	return (0);
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
		if(!(split = ft_strsplit(pbpaste_path, ' ')))
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
