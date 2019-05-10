/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 20:00:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/06 20:00:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		substitute_command_str(t_command_line *command_line, char *str)
{
	t_word	word;

	if (populate_word_by_index(command_line->dy_str->str,
		command_line->current_index, &word))
		return (FAILURE);
	if (process_substitute_command(command_line, str, word))
	{
		free(word.str);
		return (FAILURE);
	}
	free(word.str);
	return (SUCCESS);
}

int		process_autocompletion_down(t_command_line *command_line)
{
	t_file	*file;

	command_line->autocompletion.head = command_line->autocompletion.head->next;
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str(command_line, file->fullname);
	render_command_line(command_line, 0);
	return (SUCCESS);
}

int		process_autocompletion_up(t_command_line *command_line)
{
	t_file	*file;

	command_line->autocompletion.head = command_line->autocompletion.head->prev;
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str(command_line, file->fullname);
	render_command_line(command_line, 0);
	return (SUCCESS);
}

void	update_autocompletion_head_right(t_command_line *command_line)
{
	t_dlist	*ptr;
	t_file	*file;
	t_file	*file_iter;

	file = (t_file *)((command_line->autocompletion.head)->content);
	ptr = command_line->autocompletion.head->next;
	while (ptr != command_line->autocompletion.head)
	{
		file_iter = (t_file *)(ptr->content);
		if (file_iter->y == file->y && file_iter->x == file->x + 1) //go left with right
		{
			command_line->autocompletion.head = ptr;
			return ;
		}
		else if (file_iter->x == 0 && file_iter->y == file->y + 1
			&& ((command_line->autocompletion.nb_lines == 1)
			|| (command_line->autocompletion.nb_lines > 1
			&& file->x != 0)))
		{
			command_line->autocompletion.head = ptr;
			return ;
		}
		else if (file->y == command_line->autocompletion.nb_lines - 1
				&& file_iter->y == command_line->autocompletion.nb_lines - 1
					&& file_iter->x == 0) //bottom movement
		{
			command_line->autocompletion.head = ptr;
			return ;
		}
		ptr = ptr->next;
	}
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
		if (file_iter->y == file->y && file_iter->x == file->x - 1)
		{
			command_line->autocompletion.head = ptr;
			return ;
		}
		else if ((file->x == 0 && file_iter->y == file->y - 1)
		&& ((command_line->autocompletion.nb_lines == 1)
			|| (command_line->autocompletion.nb_lines > 1
			&& file_iter->x > 0)))
		{
			command_line->autocompletion.head = ptr;
			return ;
		}
		else if (file->y == 0 && file_iter->y == 0
			&& file_iter->x == command_line->autocompletion.nb_cols - 1)
		{
			command_line->autocompletion.head = ptr;
			return ;
		}
		ptr = ptr->prev;
	}
}

int		process_autocompletion_right(t_command_line *command_line)
{
	t_file	*file;

	if (command_line->autocompletion.nb_cols == 1)
	{
		command_line->autocompletion.head
			= command_line->autocompletion.head->next;
		file = (t_file *)command_line->autocompletion.head->content;
		substitute_command_str(command_line, file->fullname);
		render_command_line(command_line, 0);
		return (SUCCESS);
	}
	update_autocompletion_head_right(command_line);
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str(command_line, file->fullname);
	render_command_line(command_line, 0);
	return (SUCCESS);
}

int		process_autocompletion_left(t_command_line *command_line)
{
	t_file	*file;

	if (command_line->autocompletion.nb_cols == 1)
	{
		command_line->autocompletion.head
			= command_line->autocompletion.head->prev;
		file = (t_file *)command_line->autocompletion.head->content;
		substitute_command_str(command_line, file->fullname);
		render_command_line(command_line, 0);
		return (SUCCESS);
	}
	update_autocompletion_head_left(command_line);
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str(command_line, file->fullname);
	render_command_line(command_line, 0);
	return (SUCCESS);
}
