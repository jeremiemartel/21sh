/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:43:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/03 17:37:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_buffer(t_key_buffer buffer)
{
	int i;

	i = 0;
	ft_printf("\nprogress: %d\n\n", buffer.progress);
	while (i < buffer.progress)
	{
		ft_printf("buffer[%d]: %d (%.8b)\n", i, buffer.buff[i], buffer.buff[i]);
		i++;
	}
	ft_printf("last character input: %d\n", buffer.last_char_input);
	ft_printf("\n\n");
}

int		process_escape_sequence(t_shell *shell,
			t_command_line *command_line, t_key_buffer *buffer)
{
	command_line->searcher.active = 0;
	if ((buffer->buff[1] == 91 || buffer->buff[1] == 79) && buffer->buff[2] == 67)
		process_right(shell, command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79) && buffer->buff[2] == 68)
		process_left(shell, command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79) && buffer->buff[2] == 51)
		process_suppr(command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79) && buffer->buff[2] == 72)
		process_start(command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79) && buffer->buff[2] == 70)
		process_end(command_line);
	else if ((buffer->buff[1] == 91 && buffer->buff[2] == 49 &&
		buffer->buff[3] == 59 && buffer->buff[4] == 50))
	{
		process_shift(buffer, command_line);
		return (SUCCESS);
	}
	else
		return (SUCCESS);
	flush_keys(buffer);
	return (SUCCESS);
}

void	process_shift(t_key_buffer *buffer, t_command_line *command_line)
{
	if (buffer->buff[5] == 67
			&& command_line->current_index
				< (int)command_line->dy_str->current_size)
		process_shift_right(command_line);
	else if (buffer->buff[5] == 68)
		process_shift_left(command_line);
	else if (buffer->buff[5] == 65)
		process_shift_up(command_line);
	else if (buffer->buff[5] == 66)
		process_shift_down(command_line);
	else
		return ;
	flush_keys(buffer);
}

int		process_keys(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	if (buffer->buff[0] == 0)
		return (process_escape(shell, command_line));
	if (buffer->buff[0] == 27)
		return (process_escape_sequence(shell, command_line, buffer));
	else if (buffer->buff[0] == 12)
		process_clear(command_line);
	else if (buffer->buff[0] == 127)
		process_delete(command_line, shell);
	else if (buffer->buff[0] == 1)
		process_start(command_line);
	else if (buffer->buff[0] == 5)
		process_end(command_line);
	else
		return (SUCCESS);
	flush_keys(buffer);
	return (SUCCESS);
}

void	flush_keys(t_key_buffer *buffer)
{
	if (buffer->progress)
	{
		buffer->last_char_input = buffer->buff[0];
		ft_bzero(buffer->buff, READ_BUFF_SIZE);
		buffer->progress = 0;
	}
}

int		flush_keys_ret(t_key_buffer *buffer, int ret)
{
	flush_keys(buffer);
	return (ret);
}

int		should_flush_buffer(t_key_buffer buffer)
{
	if (buffer.buff[0] < 32 && buffer.buff[0] != 27)
	{
//		ft_printf("OLALALALLA\n");
		return (1);
	}
	else if (buffer.progress > 1 && buffer.buff[0] == 27 && buffer.buff[1] != 91)
	{
//		ft_printf("OLALALALLA\n");
		return (1);
	}

	return (0);
}

int		get_keys(t_shell *shell, t_command_line *command_line)
{
	t_key_buffer	buffer;
	int				res;

	ft_bzero(buffer.buff, READ_BUFF_SIZE);
	buffer.progress = 0;
	buffer.last_char_input = -1;
	while (1)
	{
		if (read(0, &buffer.buff[buffer.progress++], 1) < 0)
			return (sh_perror(SH_ERR1_READ, "get_keys"));
		//sh_print_buffer(buffer);//PRINT BUFFER
		process_keys(&buffer, shell, command_line);
		if (command_line->mode == E_MODE_INSERT)
		{
			res = process_keys_insert(&buffer, shell, command_line);
			if (res == FAILURE || (command_line->context != E_CONTEXT_HEREDOC
					&& res != KEEP_READ && res != CTRL_C)
					|| (command_line->context != E_CONTEXT_STANDARD
						&& res != KEEP_READ))
				return (res);
		}
		else if (process_keys_others(&buffer, shell, command_line) != SUCCESS)
			return (FAILURE);
		if (buffer.progress >= READ_BUFF_SIZE
			|| (buffer.progress && should_flush_buffer(buffer)))
		{
			ft_printf(RED"SHOULD FLUSH"EOC);
			flush_keys(&buffer);
		}
	}
}
