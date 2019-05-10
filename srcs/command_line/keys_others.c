/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:21:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 14:21:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_keys_command(unsigned char buffer[READ_BUFF_SIZE],
		t_command_line *command_line)
{
	if (buffer[0] == 'p')
		return (paste_current_index(command_line, command_line->clipboard));
	else if (buffer[0] == 'i')
		return (process_i(command_line));
	else if (buffer[0] == 'v')
		return (process_v(command_line));
	else if (buffer[0] == 'd' && command_line->last_char_input == 'd' && command_line->dy_str->current_size)
	{
		if (command_line_copy_all(command_line) != SUCCESS)
			return (FAILURE);
		flush_command_line(command_line);
		render_command_line(command_line, - g_glob.cursor);
	}
	else if (buffer[0] == 'y' && command_line->last_char_input == 'y')
		return (command_line_copy_all(command_line));
	return (SUCCESS);
}

int		process_keys_visual(unsigned char buffer[READ_BUFF_SIZE],
		t_command_line *command_line)
{
	char *new_prompt;

	if (buffer[0] == 'y')
	{
		if (copy_selection_to_clipboard(command_line) != SUCCESS)
			return (FAILURE);
		if (!(new_prompt = ft_strdup(COMMAND_PROMPT)))
			return (ft_perror(SH_ERR1_MALLOC, "process_keys_visual"));
		command_line->mode = E_MODE_COMMAND;
		switch_prompt(command_line, new_prompt);
	}
	else if (buffer[0] == 'd')
	{
		if (copy_selection_to_clipboard(command_line) != SUCCESS)
			return (FAILURE);
		if (!(new_prompt = ft_strdup(COMMAND_PROMPT)))
			return (ft_perror(SH_ERR1_MALLOC, "process_keys_visual"));
		command_line->mode = E_MODE_COMMAND;
		switch_prompt(command_line, new_prompt);
		delete_command_line_selection(command_line);
	}
	return (SUCCESS);
}

int		process_keys_others(unsigned char buffer[READ_BUFF_SIZE],
		t_command_line *command_line)
{
	if (command_line->mode == E_MODE_COMMAND)
		return (process_keys_command(buffer, command_line));
	else if (command_line->mode == E_MODE_VISUAL)
		return (process_keys_visual(buffer, command_line));
	else
		return (SUCCESS);
}
