/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 02:30:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/04 02:30:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	fill_file_tables(t_command_line *command_line, t_file ***tbl)
{
	t_file	*file;
	t_dlist	*ptr;
	int     first;
	int		i;
	int		j;

	first = 1;
	i = 0;
	j = 0;
	ptr = command_line->autocompletion.choices;
	while ((ptr != command_line->autocompletion.choices
			&& ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		file->x = j;
		file->y = i;
		tbl[i][j] = file;
		if (++i == command_line->autocompletion.nb_lines)
		{
			i = 0;
			j++;
		}
		first = 0;
		ptr = ptr->next;
	}
}

int		init_file_tables(t_command_line *command_line, t_file ****res)
{
	int		i;
	int		j;

	i = 0;
	while (i < command_line->autocompletion.nb_lines)
	{
		if (!((*res)[i] = (t_file **)malloc(sizeof(t_file *) *
				command_line->autocompletion.nb_cols)))
		{
			while (i--)
				free((*res)[i]);
			free((*res));
			return (1);
		}
		j = 0;
		while (j < command_line->autocompletion.nb_cols)
		{
			(*res)[i][j] = NULL;
			j++;
		}
		i++;
	}
	return (0);
}

t_file	***update_file_tables(t_command_line *command_line)
{
	t_file	***res;

	if (!(res = (t_file ***)malloc(sizeof(t_file **) *
			command_line->autocompletion.nb_lines)))
		return (NULL);
	if (init_file_tables(command_line, &res))
		return (NULL);
	fill_file_tables(command_line, res);
	return (res);
}

void	free_tbl(t_file ***tbl, int width)
{
	int i;

	i = 0;
	while (i < width)
	{
		free(tbl[i]);
		i++;
	}
	free(tbl);
}
