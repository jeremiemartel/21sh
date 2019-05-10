/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:43:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/09 18:34:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_buffer(unsigned char buffer[READ_BUFF_SIZE])
{
	int i;

	i = 0;
	while (i < READ_BUFF_SIZE)
	{
		ft_printf("\nbuffer[%d]: %d (%.8b)", i, buffer[i], buffer[i]);
		i++;
	}
}

void	switch_prompt(t_command_line *command_line, char *new_prompt)
{
	free(command_line->prompt);
	command_line->prompt = new_prompt;
	render_command_line(command_line, 0);
}

int		process_escape(t_command_line *command_line)
{
	char *new_prompt;

	if (!(new_prompt = ft_strdup(COMMAND_PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "process_escape"));
	command_line->autocompletion.active = 0;
	command_line->autocompletion.head = NULL;
	switch_prompt(command_line, new_prompt);
	command_line->mode = E_MODE_COMMAND;
	return (SUCCESS);
}

int		process_escape_sequence(t_shell *shell, t_command_line *command_line,
		unsigned char buffer[READ_BUFF_SIZE])
{
	if (!(buffer[1] | buffer[2] | buffer[3]))
		return (process_escape(command_line));
	else if (buffer[1] == 91 && buffer[2] == 67)
		process_right(shell, command_line);
	else if (buffer[1] == 91 && buffer[2] == 68)
		process_left(shell, command_line);
	else if (buffer[1] == 91 && buffer[2] == 51)
		process_suppr(command_line);
	else if (buffer[1] == 91 && buffer[2] == 72)
		process_start(command_line);
	else if (buffer[1] == 91 && buffer[2] == 70)
		process_end(command_line);
	return (0);
}

void	process_shift(t_command_line *command_line,
			unsigned char buffer[READ_BUFF_SIZE])
{
	if (buffer[1] == 67)
		process_shift_right(command_line);
	else if (buffer[1] == 68)
		process_shift_left(command_line);
	else if (buffer[1] == 65)
		process_shift_up(command_line);
	else if (buffer[1] == 66)
		process_shift_down(command_line);
}

int		process_keys(t_shell *shell, t_command_line *command_line,
				unsigned char *buffer)
{
	if (buffer[0] == 27)
		return (process_escape_sequence(shell, command_line, buffer));
	else if (buffer[0] == 12)
		process_clear(command_line);
	else if (buffer[0] == 127)
		process_delete(command_line);
	else if (buffer[0] == 50)
		process_shift(command_line, buffer);
	
	return (SUCCESS);
}

int		process_keys_ret(t_shell *shell, t_command_line *command_line,
			unsigned char *buffer)
{
	if (buffer[0] == 10) // enter
	{
		if (command_line->autocompletion.head == NULL)
		{
			get_down_from_command(command_line);
			command_line->dy_str->current_size = 0;
			return (0);
		}
		else
		{
			substitute_current_index(command_line, command_line->autocompletion.head->content);
			command_line->autocompletion.head = NULL;
			command_line->autocompletion.active = 0;
			render_command_line(command_line, 0);
		}
	}
	else if (buffer[0] == 4) //ctrl D
	{
		if (command_line->dy_str->current_size == 0)
		{
			ft_dprintf(0, "exit\n");
			shell->running = 0;
			return (CTRL_D);
		}
	}
	else if (buffer[0] == 9 && process_tab(shell, command_line) != SUCCESS)
		return (FAILURE);
	return (4);
}

int command_line_copy_all(t_command_line *command_line)
{
	if (command_line->clipboard != NULL)
		free(command_line->clipboard);
	if (!(command_line->clipboard = ft_strdup(command_line->dy_str->str)))
		return (ft_perror(SH_ERR1_MALLOC, "command_line_copy_all"));
	return (SUCCESS);
}

int		process_i(t_command_line *command_line)
{
	char *new_prompt;

	if (!(new_prompt = ft_strdup(PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "process_i"));
	switch_prompt(command_line, new_prompt);
	command_line->mode = E_MODE_INSERT;
	return (SUCCESS);
}

int		process_v(t_command_line *command_line)
{
	char *new_prompt;

	if (!(new_prompt = ft_strdup(VISUAL_PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "process_v"));
	switch_prompt(command_line, new_prompt);
	command_line->mode = E_MODE_VISUAL;
	command_line->pinned_index = command_line->current_index;
	return (SUCCESS);
}

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

int		copy_selection_to_clipboard(t_command_line *command_line)
{
	int n;
	int index;

	n = ft_abs(command_line->current_index - command_line->pinned_index) + 1;
	index = ft_min(command_line->current_index, command_line->pinned_index);
	if (!(command_line->clipboard = ft_strndup(&command_line->dy_str->str[index], n)))
		return (ft_perror(SH_ERR1_MALLOC, "copy_selection_to_clipboard"));
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

int		process_keys_insert(unsigned char buffer[READ_BUFF_SIZE],
			t_shell *shell, t_command_line *command_line, int ret)
{
	if (buffer[0] != 10 && buffer[0] != 9
			&& (buffer[0] != 27 || buffer[1] != 91
			|| (buffer[2] < 65 || buffer[2] > 68))) //if no autocompletion relative keys
	{
		// shell->historic.head = &shell->historic.head_start;
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
	}
	//		print_buffer(buffer);
	if (is_printable_utf8(buffer, ret))
	{
		if (sh_add_to_command(command_line, buffer, ret))
			return (1);
		render_command_line(command_line, 1);
	}
	else if (buffer[0] == 3)
	{
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
		get_down_from_command(command_line);
		reset_command_line(shell, command_line);
		render_command_line(command_line, 0);
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		process_up(shell, command_line);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		process_down(shell, command_line);
	ret = process_keys_ret(shell, command_line, buffer);
	if (ret == CTRL_D || ret == 0 || ret == FAILURE)
		return (ret);
	return (4);
}

int		get_keys(t_shell *shell, t_command_line *command_line)
{
	unsigned char	buffer[READ_BUFF_SIZE];
	int				ret;
	int				res;
	int				returned;

	returned = 0;
	ft_bzero(buffer, READ_BUFF_SIZE);
	while (1)
	{
		ret = read(0, buffer, READ_BUFF_SIZE);
		process_keys(shell, command_line, buffer);
		if (command_line->mode == E_MODE_INSERT)
		{
			if ((res = process_keys_insert(buffer,
					shell, command_line, ret)) != 4)
				return (res);
		}
		else if (process_keys_others(buffer, command_line) != SUCCESS)
			return (FAILURE);
		command_line->last_char_input = buffer[0];
		ft_bzero(buffer, READ_BUFF_SIZE);
	}
	return (SUCCESS);
}
