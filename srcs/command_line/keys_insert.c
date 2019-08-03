/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:17:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/03 16:20:49 by ldedier          ###   ########.fr       */
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

/*
** Plus jamais
**
**	else if (buffer->buff[0] == 16)
**	{
**		if ((ret = process_clipboard_shell(shell, command_line)))
**			return (ret);
**	}
*/

int		process_keys_ret(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	int ret;

	if (buffer->buff[0] == 10)
	{
	//	ft_printf(RED"ENTER\n"EOC);
		if (process_enter(command_line) == 0)
			return (SUCCESS);
	}
	else if (buffer->buff[0] == 4)
	{
		if (process_ctrl_d(shell, command_line) != KEEP_READ)
			return (CTRL_D);
	}
	else if (buffer->buff[0] == 9)
	{
		if (process_tab(shell, command_line) != SUCCESS)
			return (FAILURE);
		flush_keys(buffer);
	}
	else if (buffer->buff[0] == 3)
	{
		ret = (process_ctrl_c(shell, command_line));
		return (flush_keys_ret(buffer, ret));
	}
	else
		return (KEEP_READ);
	flush_keys(buffer);
	return (KEEP_READ);
}

int		process_key_insert_printable_utf8(t_key_buffer *buffer,
		t_shell *shell, t_command_line *command_line)
{
	unsigned char c;

	if (command_line->searcher.active)
	{
		if (sh_add_to_dy_str(command_line->searcher.dy_str, buffer->buff,
			buffer->progress))
			return (FAILURE);
		c = 0;
		if (sh_add_to_dy_str(command_line->searcher.dy_str, &c, 1))
			return (FAILURE);
		update_research_historic(command_line, shell, 0);
	}
	else
	{
		if (sh_add_to_command(command_line, buffer->buff, buffer->progress))
			return (FAILURE);
		render_command_line(command_line, 1, 1);
	}
	flush_keys(buffer);
	return (SUCCESS);
}

int		process_keys_insert(t_key_buffer *buffer,
		t_shell *shell, t_command_line *command_line)
{
	if ((buffer->progress == 1 &&
		(buffer->buff[0] != 10 && buffer->buff[0] != 9
		 	&& buffer->buff[0] != 27))
		|| (buffer->progress == 2 &&
			(buffer->buff[1] != 91 && buffer->buff[1] != 79))
			|| (buffer->progress == 3 &&
				(buffer->buff[2] < 65 || buffer->buff[2] > 68)))
	{
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
	}
	if (is_printable_utf8(buffer->buff, buffer->progress))
	{
		if (process_key_insert_printable_utf8(buffer,
				shell, command_line) != SUCCESS)
			return (FAILURE);
	}
	else if (buffer->buff[0] == 27
		&& (buffer->buff[1] == 91 || buffer->buff[1] == 79)
			&& buffer->buff[2] == 65)
		process_up(shell, command_line);
	else if (buffer->buff[0] == 27
		&& (buffer->buff[1] == 91 || buffer->buff[1] == 79)
			&& buffer->buff[2] == 66)
		process_down(shell, command_line);
	else if (buffer->buff[0] == 18)
	{
		if (process_research_historic(command_line, shell))
			return (FAILURE);
	}
	else
		return (process_keys_ret(buffer, shell, command_line));
	flush_keys(buffer);
	return (KEEP_READ);
}
