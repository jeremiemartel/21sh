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

int		substitute_current_index(t_command_line *command_line, t_file *file)
{
	t_word word;
	char *to_replace;

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
