/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:39:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/20 16:51:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	ring_bell(void)
{
	char *str;

	str = tgetstr("bl", NULL);
	tputs(str, 1, putchar_int);
}

void	process_delete(t_command_line *command_line)
{
	int diff;
	int left_w_char_index;

	if (command_line->current_index == 0)
		ring_bell();
	else
	{
		left_w_char_index = get_left_w_char_index(command_line);
		diff = command_line->current_index - left_w_char_index;
		while (left_w_char_index + diff <= (int)command_line->dy_str->current_size)
		{
			command_line->dy_str->str[left_w_char_index] =
				command_line->dy_str->str[left_w_char_index + diff];
			left_w_char_index++;
		}
		command_line->current_index -= diff;
		command_line->dy_str->current_size -= diff;
		command_line->nb_chars--;
		render_command_line(command_line, -1);
	}
}

void	process_suppr(t_command_line *command_line)
{
	int diff;
	int i;

	if (command_line->current_index == (int)command_line->dy_str->current_size)
		ring_bell();
	else
	{
		diff = get_right_w_char_index(command_line) - command_line->current_index;
		i = command_line->current_index;
		while (i + diff <= (int)command_line->dy_str->current_size)
		{
			command_line->dy_str->str[i] = command_line->dy_str->str[i + diff];
			i++;
		}
		command_line->dy_str->current_size -= diff;
		command_line->nb_chars--;
		render_command_line(command_line, 0);
	}
}

void	process_edit_command_left(t_command_line *command_line)
{
	if (command_line->current_index > 0)
	{
		command_line->current_index = get_left_w_char_index(command_line);
		render_command_line(command_line, -1);
	}
	else
		ring_bell();
}

void	process_edit_command_right(t_command_line *command_line)
{
	if (command_line->current_index < (int)command_line->dy_str->current_size)
	{
		command_line->current_index = get_right_w_char_index(command_line);
		render_command_line(command_line, 1);
	}
	else
		ring_bell();
}
