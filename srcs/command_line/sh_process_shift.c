/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:27:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 14:59:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_shift_right(t_command_line *c_line)
{
	int		index;
	t_word	word;

	index = c_line->current_index + 1;
	if (populate_word_by_index(c_line->dy_str->str, index, &word)
		!= SUCCESS)
		return (FAILURE);
	if (word.len)
	{
		c_line->current_index += word.len - word.index_byte_offset + 1;
		render_command_line(c_line,
			word.utf8_len - word.index_char_offset + 1, 1);
		return (ft_del_turn_char(&word.str, SUCCESS));
	}
	ft_strdel(&word.str);
	while (index < (int)c_line->dy_str->current_size)
	{
		if (populate_word_by_index(c_line->dy_str->str, index, &word)
			!= SUCCESS)
			return (FAILURE);
		if (word.len)
			break ;
		else
			ft_strdel(&word.str);
		index++;
	}
	render_command_line(c_line, index - c_line->current_index - 1, 1);
	c_line->current_index = index - 1;
	return (ft_del_turn_char(&word.str, SUCCESS));
}

int		process_shift_left(t_command_line *command_line)
{
	int		index;
	t_word	word;

	index = command_line->current_index;
	if (populate_word_by_index(command_line->dy_str->str, index, &word)
		!= SUCCESS)
		return (FAILURE);
	if (word.len)
	{
		command_line->current_index -= word.index_byte_offset;
		render_command_line(command_line, -word.index_char_offset, 1);
		return (ft_del_turn_char(&word.str, SUCCESS));
	}
	else
		ft_strdel(&word.str);
	while (index > 0)
	{
		if (populate_word_by_index(command_line->dy_str->str, index, &word)
			!= SUCCESS)
			return (FAILURE);
		if (word.len)
			break ;
		else
			ft_strdel(&word.str);
		index--;
	}
	render_command_line(command_line, -(command_line->current_index - index), 1);
	command_line->current_index = index;
	return (ft_del_turn_char(&word.str, SUCCESS));
}

int		process_shift_up(t_command_line *command_line)
{
	int		cursor;
	t_xy	xy;
	t_xy	xy_iter;

	cursor = g_glob.cursor;
	xy = get_position(get_true_cursor_pos(g_glob.cursor));
	while (command_line->current_index > 0)
	{
		command_line->current_index = get_left_w_char_index(command_line);
		xy_iter = get_position(get_true_cursor_pos(--cursor));
		if (xy_iter.x == xy.x && xy_iter.y == xy.y - 1)
		{
			render_command_line(command_line, cursor - g_glob.cursor, 1);
			return (SUCCESS);
		}
	}
	render_command_line(command_line, cursor - g_glob.cursor, 1);
	return (SUCCESS);
}

int		process_shift_down(t_command_line *command_line)
{
	int		cursor;
	t_xy	xy;
	t_xy	xy_iter;

	cursor = g_glob.cursor;
	xy = get_position(get_true_cursor_pos(g_glob.cursor));
	while (command_line->current_index
		< (int)command_line->dy_str->current_size)
	{
		command_line->current_index = get_right_w_char_index(command_line);
		xy_iter = get_position(get_true_cursor_pos(++cursor));
		if (xy_iter.x == xy.x && xy_iter.y == xy.y + 1)
		{
			render_command_line(command_line, cursor - g_glob.cursor, 1);
			return (SUCCESS);
		}
	}
	render_command_line(command_line, cursor - g_glob.cursor, 1);
	return (SUCCESS);
}
