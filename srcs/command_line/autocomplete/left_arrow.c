/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 01:40:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 00:12:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_update_autocompletion_head_left(t_command_line *command_line,
		t_file *file_iter, t_file *file, t_dlist *ptr)
{
	if (file_iter->y == file->y && file_iter->x == file->x - 1)
	{
		command_line->autocompletion.head = ptr;
		return (1);
	}
	else if ((file->x == 0 && file_iter->y == file->y - 1)
			&& ((command_line->autocompletion.nb_lines == 1)
				|| (command_line->autocompletion.nb_lines > 1
					&& file_iter->x > 0)))
	{
		command_line->autocompletion.head = ptr;
		return (1);
	}
	else if (file->y == 0 && file_iter->y == 0
			&& file_iter->x == command_line->autocompletion.nb_cols - 1)
	{
		command_line->autocompletion.head = ptr;
		return (1);
	}
	return (0);
}

void	update_autocompletion_head_left(t_command_line *command_line)
{
	t_dlist	*ptr;
	t_file	*file;
	t_file	*file_iter;

	file = (t_file *)((command_line->autocompletion.head)->content);
	ptr = command_line->autocompletion.head->prev;
	while (ptr != command_line->autocompletion.head)
	{
		file_iter = (t_file *)(ptr->content);
		if (process_update_autocompletion_head_left(command_line,
				file_iter, file, ptr))
			return ;
		ptr = ptr->prev;
	}
}

int		process_autocompletion_left(t_command_line *command_line)
{
	t_file	*file;
	t_file	*prev_file;

	prev_file = command_line->autocompletion.head->content;
	if (command_line->autocompletion.nb_cols == 1)
	{
		command_line->autocompletion.head =
			command_line->autocompletion.head->prev;
		file = (t_file *)command_line->autocompletion.head->content;
		substitute_command_str_from_str(command_line,
			prev_file->fullname, file->fullname);
		process_autocompletion_switch(command_line, prev_file, file);
		return (SUCCESS);
	}
	update_autocompletion_head_left(command_line);
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str_from_str(command_line,
		prev_file->fullname, file->fullname);
	process_autocompletion_switch(command_line, prev_file, file);
	return (SUCCESS);
}
