/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:43:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/21 14:40:29 by jmartel          ###   ########.fr       */
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
	ft_printf("\n\n");
}

int		process_escape_sequence(t_shell *shell, t_command_line *command_line,
		unsigned char buffer[READ_BUFF_SIZE])
{
	command_line->searcher.active = 0;
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
	if (buffer[1] == 67
			&& command_line->current_index
				< (int)command_line->dy_str->current_size)
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
		process_delete(command_line, shell);
	else if (buffer[0] == 50)
		process_shift(command_line, buffer);
	return (SUCCESS);
}

int		get_keys(t_shell *shell, t_command_line *command_line)
{
	unsigned char	buffer[READ_BUFF_SIZE];
	int				ret;
	int				res;

	ft_bzero(buffer, READ_BUFF_SIZE);
	while (1)
	{
		ret = read(0, buffer, READ_BUFF_SIZE);
//			print_buffer(buffer);
		process_keys(shell, command_line, buffer);
		if (command_line->mode == E_MODE_INSERT)
		{
			 res = process_keys_insert(buffer, shell, command_line, ret);
			if (command_line->context == E_CONTEXT_STANDARD
				&& res != KEEP_READ && res != CTRL_C)
					return (res);
			else if (command_line->context == E_CONTEXT_HEREDOC
				&& res != KEEP_READ)
					return (res);
		}
		else if (process_keys_others(buffer, command_line) != SUCCESS)
			return (FAILURE);
		command_line->last_char_input = buffer[0];
		ft_bzero(buffer, READ_BUFF_SIZE);
	}
	return (SUCCESS);
}
