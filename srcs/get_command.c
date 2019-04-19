/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:31:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 16:51:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** cursor_inc: tells the cursor movement to execute within the render of the
** command_line
*/

int		render_command_line(t_dy_str *dy_str, int cursor_inc)
{
	char	*str;

	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.cursor);
	str = tgetstr("cd", NULL);
	tputs(str, 1, putchar_int);
	ft_dprintf(0, "%s%s%s%s", BOLD, CYAN, g_glob.command_line.prompt, EOC);
	ft_dprintf(0, "%s", dy_str->str);
	g_glob.cursor += cursor_inc;
	replace_cursor_after_render();
	return (0);
}

int		sh_add_to_command(t_command_line *command_line,
		unsigned char buffer[READ_BUFF_SIZE], int nb_bytes)
{
	int i;

	i = 0;
	while (i < nb_bytes)
	{
		if (ft_dy_str_add_index(command_line->dy_str, (char)buffer[i],
				command_line->current_index++))
			return (1);
		i++;
	}
	command_line->nb_chars++;
	return (0);
}

void	reset_command_line(t_shell *shell, t_command_line *command_line)
{
	shell->historic.head = &shell->historic.head_start;
	g_glob.cursor = 0;
	flush_command_line(command_line);
}

int		sh_get_command(t_shell *shell, t_command_line *command_line)
{
	int		ret;

	reset_command_line(shell, command_line);
	render_command_line(command_line->dy_str, 0);
	if ((ret = get_keys(shell, command_line)))
		return (ret);
	return (0);
}
