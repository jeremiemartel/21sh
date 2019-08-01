/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:21:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/01 17:31:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_keys_command(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	if (buffer->buff[0] == 'p')
		return (paste_current_index(command_line, command_line->clipboard));
	else if (buffer->buff[0] == 'i')
		return (process_i(shell, command_line));
	else if (buffer->buff[0] == 'v')
		return (process_v(shell, command_line));
	else if (buffer->buff[0] == 'd' && buffer->last_char_input == 'd'
		&& command_line->dy_str->current_size)
	{
		if (command_line_copy_all(command_line) != SUCCESS)
			return (FAILURE);
		flush_command_line(command_line);
		render_command_line(command_line, -g_glob.cursor, 1);
	}
	else if (buffer->buff[0] == 'y' && buffer->last_char_input == 'y')
		return (command_line_copy_all(command_line));
	return (SUCCESS);
}

int		process_keys_visual(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	if (buffer->buff[0] == 'y')
	{
		if (copy_selection_to_clipboard(command_line) != SUCCESS)
			return (FAILURE);
		command_line->mode = E_MODE_COMMAND;
		update_prompt(shell, command_line);
		render_command_line(command_line, 0, 1);
		flush_keys(buffer);
	}
	else if (buffer->buff[0] == 'd')
	{
		if (copy_selection_to_clipboard(command_line) != SUCCESS)
			return (FAILURE);
		command_line->mode = E_MODE_COMMAND;
		update_prompt(shell, command_line);
		delete_command_line_selection(command_line);
		render_command_line(command_line, 0, 1);
		flush_keys(buffer);
	}
	return (SUCCESS);
}

int		process_keys_others(t_key_buffer *buffer,
			t_shell *shell, t_command_line *command_line)
{
	if (command_line->mode == E_MODE_COMMAND)
		return (process_keys_command(buffer, shell, command_line));
	else if (command_line->mode == E_MODE_VISUAL)
		return (process_keys_visual(buffer, shell, command_line));
	else
		return (SUCCESS);
}
