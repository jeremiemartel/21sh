/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:27:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/18 16:27:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_shift_right(t_command_line *command_line)
{
	int		index;
	t_word	word;

	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (SUCCESS);
	index = command_line->current_index + 1;
	if (populate_word_by_index(command_line->dy_str->str, index, &word)
		!= SUCCESS)
		return (FAILURE);
	if (word.len)
	{
		command_line->current_index += word.len - word.index_byte_offset + 1;
		render_command_line(command_line->dy_str, word.utf8_len - word.index_char_offset + 1);
		return (SUCCESS);
	}
	while (index < (int)command_line->dy_str->current_size)
	{
		if (populate_word_by_index(command_line->dy_str->str, index, &word)
			!= SUCCESS)
			return (FAILURE);
		if (word.len)
			break;
		index++;
	}
	render_command_line(command_line->dy_str, index - command_line->current_index - 1);
	command_line->current_index = index - 1;
	return (0);
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
		render_command_line(command_line->dy_str, - word.index_char_offset);
		return (SUCCESS);
	}
	while (index > 0)
	{
		if (populate_word_by_index(command_line->dy_str->str, index, &word)
			!= SUCCESS)
			return (FAILURE);
		if (word.len)
			break;
		index--;
	}
	render_command_line(command_line->dy_str, - (command_line->current_index - index)); //olala
	command_line->current_index = index;
	return (0);
}
