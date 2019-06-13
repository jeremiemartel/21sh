/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:51:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
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

int		process_substitute_command(t_command_line *command_line, char *str,
		t_word word, int print_choices)
{
	int len;
	int utf8_len;

	len = ft_strlen(str);
	utf8_len = ft_strlen_utf8(str);
	if (ft_substitute_dy_str(command_line->dy_str, str,
		word.start_index, word.len))
		return (1);
	command_line->current_index += (len - word.index_byte_offset);
	command_line->nb_chars += (utf8_len - word.utf8_len);
	render_command_line(command_line, utf8_len - word.index_char_offset,
		print_choices);
	return (0);
}

int		substitute_current_index(t_command_line *command_line, t_file *file)
{
	t_word	word;
	char	*to_replace;

	if (populate_word_by_index(command_line->dy_str->str,
			command_line->current_index, &word) == FAILURE)
		return (FAILURE);
	if (!(to_replace = get_completion_str_file(file)))
		return (sh_perror(SH_ERR1_MALLOC, "substitute_current_index"));
	{
		free(word.str);
		return (sh_perror(SH_ERR1_MALLOC, "substitute_current_index"));
	}
	if (process_substitute_command(command_line, to_replace, word, 1))
	{
		free(word.str);
		free(to_replace);
		return (FAILURE);
	}
	free(word.str);
	free(to_replace);
	return (SUCCESS);
}

int		command_line_nb_rows(t_command_line *command_line)
{
	return ((ft_strlen_utf8(command_line->dy_str->str) +
				ft_strlen_utf8(command_line->prompt))
					/ g_glob.winsize.ws_col + 1);
}
