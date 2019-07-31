/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:19:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 10:36:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*refine_historic_entry(char *entry)
{
	int		len;
	char	*new;
	int		i;

	i = 0;
	len = ft_strlen(entry);
	if (!(new = ft_strnew(len)))
		return (sh_perrorn(SH_ERR1_MALLOC, "refine_historic_entry"));
	while (entry[i])
	{
		if (!ft_isascii(entry[i]) || !ft_isprint(entry[i]))
		{
			new[i] = ' ';
		}
		else
			new[i] = entry[i];
		i++;
	}
	return (new);
}

int		process_read_historic(t_historic *historic, char *line)
{
	char *res;

	if (!(res = refine_historic_entry(line)))
	{
		free(line);
		return (FAILURE);
	}
	free(line);
	if (ft_add_to_dlist_ptr(&historic->commands, res, sizeof(res)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_init_historic"));
	return (SUCCESS);
}

int		sh_init_historic(t_historic *historic)
{
	int			fd;
	char		*line;
	int			ret;

	historic->commands = NULL;
	if ((fd = open(HISTORIC_FILE, O_CREAT | O_RDWR | O_NOFOLLOW,
		S_IRWXU)) == -1)
		return (sh_perror(SH_ERR1_HISTORIC, "sh_init_historic"));
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (process_read_historic(historic, line) != SUCCESS)
			return (FAILURE);
	}
	if (ret == -1)
		return (FAILURE);
	free(line);
	historic->head_start.next = historic->commands;
	historic->head_start.prev = NULL;
	historic->head = &historic->head_start;
	close(fd);
	return (SUCCESS);
}

int		sh_init_command_line(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.choices = NULL;
	command_line->autocompletion.head = NULL;
	command_line->autocompletion.active = 0;
	command_line->interrupted = 0;
	command_line->autocompletion.scrolled_lines = 0;
	command_line->pinned_index = -1;
	command_line->last_char_input = -1;
	command_line->mode = E_MODE_INSERT;
	command_line->context = E_CONTEXT_STANDARD;
	if (!(command_line->searcher.dy_str = ft_dy_str_new(63)))
		return (FAILURE);
	command_line->searcher.active = 0;
	command_line->searcher.head = NULL;
	command_line->searcher.unsuccessful = 0;
	command_line->prompt = NULL;
	command_line->to_append = 0;
	command_line->to_append_str = NULL;
	if (update_prompt(shell, command_line) == FAILURE)
		return (FAILURE);
	command_line->clipboard = NULL;
	if (!(command_line->dy_str = ft_dy_str_new(63)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_init_command_line"));
	return (SUCCESS);
}

int		sh_init_shell(t_shell *shell, char **env)
{
	struct termios s;

	s = shell->term;
	ft_bzero(shell, sizeof(t_shell));
	ft_bzero(&g_glob.command_line, sizeof(t_command_line));
	if (isatty(0))
		if (ioctl(0, TIOCGWINSZ, &g_glob.winsize) == -1)
			return (sh_perror(SH_ERR1_IOCTL, "sh_init_shell"));
	shell->term = s;
	shell->ret_value = 0;
	shell->ret_value_set = 0;
	if (sh_main_init_env(shell, env) == FAILURE)
		return (FAILURE);
	if (sh_main_init_vars(shell) == FAILURE)
		return (FAILURE);
	if (sh_init_command_line(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	shell->running = 1;
	if (sh_init_parsing(&shell->parser) != SUCCESS)
		return (FAILURE);
	if ((sh_init_historic(&shell->historic)) != SUCCESS)
		return (FAILURE);
	if (!(shell->binaries = ft_hash_table_new(BINARIES_TABLE_SIZE)))
		return (FAILURE);
	return (SUCCESS);
}
