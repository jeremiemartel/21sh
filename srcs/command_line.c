/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:51:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/09 14:51:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	flush_command_line(t_command_line *command_line)
{
	command_line->dy_str->current_size = 0;
	command_line->current_index = 0;
	ft_bzero(command_line->dy_str->str, command_line->dy_str->max_size);
	command_line->nb_chars = 0;
}

int     process_substitute_command(t_command_line *command_line, char *str,
		t_word word)
{
	int len;
	int utf8_len;

	len = ft_strlen(str);
	utf8_len = ft_strlen_utf8(str);
	if (ft_substitute_dy_str(command_line->dy_str, str, word.start_index, word.len))
		return (1);
	command_line->current_index += (len - word.index_byte_offset);
	command_line->nb_chars += (utf8_len - word.utf8_len);
	render_command_line(command_line, utf8_len - word.index_char_offset);
	return (0);
}

int		substitute_current_index(t_command_line *command_line, t_file *file)
{
	t_word	word;
	char	*to_replace;

	populate_word_by_index(command_line->dy_str->str, command_line->current_index, &word);
	if (!(to_replace = get_completion_str_file(file)))
		return (ft_perror(SH_ERR1_MALLOC, "substitute_current_index"));
	if (process_substitute_command(command_line, to_replace, word))
	{
		free(to_replace);
		return (FAILURE);
	}
	return (SUCCESS);
}

int		paste_current_index(t_command_line *command_line, char *to_paste)
{
	int utf8_len;
	int len;

	if (!to_paste)
		return (SUCCESS);
	len = ft_strlen(to_paste);
	utf8_len = ft_strlen_utf8(to_paste);
	if (ft_substitute_dy_str(command_line->dy_str, to_paste, command_line->current_index, 0))
		return (ft_perror(SH_ERR1_MALLOC, "paste_current_index"));
	command_line->current_index += len;
	command_line->nb_chars += utf8_len;
	render_command_line(command_line, utf8_len);
	return (SUCCESS);
}

int		delete_command_line_selection(t_command_line *command_line)
{
	int min;
	int max;
	int len;
	int utf8_len;

	populate_min_max_selection(command_line, &min, &max);
	if (max == (int)command_line->dy_str->current_size)
		len = max - min;
	else
		len = max - min + 1;
	utf8_len = ft_strnlen_utf8(&command_line->dy_str->str[min], len);
	if (ft_substitute_dy_str(command_line->dy_str, "", min, len))
		return (ft_perror(SH_ERR1_MALLOC, "delete_command_line_selection"));
	command_line->nb_chars -= utf8_len;
	if (command_line->current_index == min)
		render_command_line(command_line, 0);
	else
	{
		command_line->current_index -= len;
		render_command_line(command_line, - utf8_len);
	}
	return (SUCCESS);
}
