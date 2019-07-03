/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:17:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/15 17:32:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_enter_no_autocompletion(t_command_line *command_line)
{
	command_line->autocompletion.active = 0;
	command_line->searcher.active = 0;
	render_command_line(command_line, 0, 0);
	get_down_from_command(command_line);
	command_line->dy_str->current_size = 0;
	return (0);
}

int		process_enter(t_command_line *command_line)
{
	if (command_line->autocompletion.head == NULL)
		return (process_enter_no_autocompletion(command_line));
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

int		process_keys_ret(t_shell *shell, t_command_line *command_line,
		unsigned char *buffer)
{
	int ret;

	if (buffer[0] == 10)
	{
		if (process_enter(command_line) == 0)
			return (SUCCESS);
	}
	else if (buffer[0] == 4)
	{
		if (process_ctrl_d(shell, command_line) != KEEP_READ)
			return (CTRL_D);
	}
	else if (buffer[0] == 16)
	{
		if ((ret = process_clipboard_shell(shell, command_line)))
			return (ret);
	}
	else if (buffer[0] == 9 && process_tab(shell, command_line) != SUCCESS)
		return (FAILURE);
	else if (buffer[0] == 3)
		return (process_ctrl_c(shell, command_line));
	return (KEEP_READ);
}

int		process_key_insert_printable_utf8(unsigned char buffer[READ_BUFF_SIZE],
		t_shell *shell, t_command_line *command_line, int ret)
{
	if (command_line->searcher.active)
	{
		if (sh_add_to_dy_str(command_line->searcher.dy_str, buffer, ret))
			return (FAILURE);
		buffer[0] = 0;
		if (sh_add_to_dy_str(command_line->searcher.dy_str, buffer, 1))
			return (FAILURE);
		update_research_historic(command_line, shell, 0);
	}
	else
	{
		if (sh_add_to_command(command_line, buffer, ret))
			return (FAILURE);
		render_command_line(command_line, 1, 1);
	}
	return (SUCCESS);
}

int		process_keys_insert(unsigned char buffer[READ_BUFF_SIZE],
		t_shell *shell, t_command_line *command_line, int ret)
{
	if (buffer[0] != 10 && buffer[0] != 9
			&& (buffer[0] != 27 || buffer[1] != 91
				|| (buffer[2] < 65 || buffer[2] > 68)))
	{
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
	}
	if (is_printable_utf8(buffer, ret))
	{
		if (process_key_insert_printable_utf8(buffer,
				shell, command_line, ret) != SUCCESS)
			return (FAILURE);
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		process_up(shell, command_line);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		process_down(shell, command_line);
	else if (buffer[0] == 18 && process_research_historic(command_line, shell))
		return (FAILURE);
	return (process_keys_ret(shell, command_line, buffer));
}
