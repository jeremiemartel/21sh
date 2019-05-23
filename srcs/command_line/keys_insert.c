/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:17:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/23 11:37:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_enter(t_command_line *command_line)
{
	if (command_line->autocompletion.head == NULL)
	{
		command_line->autocompletion.active = 0;
		command_line->searcher.active = 0;
		render_command_line(command_line, 0, 0);
		get_down_from_command(command_line);
		command_line->dy_str->current_size = 0;
		return (0);
	}
	else
	{
		substitute_current_index(command_line,
			command_line->autocompletion.head->content);
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
		render_command_line(command_line, 0, 1);
	}
	return (1);
}


void		process_ctrl_c(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.head = NULL;
	command_line->autocompletion.active = 0;
	if (command_line->searcher.active == 0)
		get_down_from_command(command_line);
	command_line->searcher.active = 0;
	reset_command_line(shell, command_line);
	render_command_line(command_line, 0, 1);
}

int		process_keys_ret(t_shell *shell, t_command_line *command_line,
		unsigned char *buffer)
{
	if (buffer[0] == 10)
	{
		if (process_enter(command_line) == 0)
			return (0);
	}
	else if (buffer[0] == 4) //ctrl D
	{
		if (command_line->dy_str->current_size == 0)
		{
			if (command_line->context == E_CONTEXT_STANDARD)
			{
				shell->running = 0;
				ft_dprintf(0, "exit\n");
			}
			return (CTRL_D);
		}
	}
	else if (buffer[0] == 9 && process_tab(shell, command_line) != SUCCESS)
		return (FAILURE);
	else if (buffer[0] == 3)
	{
		process_ctrl_c(shell, command_line);
		return (CTRL_C);
	}
	return (KEEP_READ);
}

int		process_keys_insert(unsigned char buffer[READ_BUFF_SIZE],
		t_shell *shell, t_command_line *command_line, int ret)
{
	if (buffer[0] != 10 && buffer[0] != 9
			&& (buffer[0] != 27 || buffer[1] != 91
				|| (buffer[2] < 65 || buffer[2] > 68))) //if no autocompletion relative keys
	{
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
	}
	if (is_printable_utf8(buffer, ret))
	{
		if (command_line->searcher.active)
		{
			if (sh_add_to_dy_str(command_line->searcher.dy_str, buffer, ret))
				return (FAILURE);
			buffer[0] = 0;
			if (sh_add_to_dy_str(command_line->searcher.dy_str, buffer, 1))
				return (FAILURE);
			render_command_line(command_line, 0, 0);
			update_research_historic(command_line, shell, 0);
		}
		else
		{
			if (sh_add_to_command(command_line, buffer, ret))
				return (1);
			render_command_line(command_line, 1, 1);
		}
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		process_up(shell, command_line);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		process_down(shell, command_line);
	else if (buffer[0] == 18 && process_research_historic(command_line, shell))
		return (FAILURE);
	return (process_keys_ret(shell, command_line, buffer));
}
