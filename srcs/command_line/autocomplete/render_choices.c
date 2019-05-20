/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/17 20:34:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_get_file_len(t_file *file)
{
	return (ft_strlen_utf8(file->name) + S_ISDIR(file->st.st_mode));
}

static int	sh_get_max_file_len(t_dlist *dlist)
{
	t_dlist	*ptr;
	t_file	*file;
	int		first;
	int		ret;
	int		max;

	max = 0;
	ptr = dlist;
	first = 1;
	while ((ptr != dlist && ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		if ((ret = sh_get_file_len(file)) > max)
			max = ret;
		ptr = ptr->next;
		first = 0;
	}
	return (max);
}


int		ft_round(float a)
{
	if (a == (int) a)
		return ((int)a);
	else
		return ((int)a + 1);
}

static int	lines_rendered_from_file(t_file *file)
{
	return (ft_max(1, (sh_get_file_len(file) / g_glob.winsize.ws_col) + 1));
}

int		command_line_visible_lines(t_command_line *command_line)
{
	t_dlist *ptr;
	int		res;
	int		first;
	t_file	*file;

	if (command_line->autocompletion.nb_cols > 1)
		return (command_line->autocompletion.nb_lines);
	first = 1;
	res = 0;
	ptr = command_line->autocompletion.choices;
	while ((ptr != command_line->autocompletion.choices
		&& ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		first = 0;
		res += lines_rendered_from_file(file);
		ptr = ptr->next;
	}
	return (res);
}

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

t_file	***update_file_tables(t_command_line *command_line)
{
	t_file	***res;
	int		i;
	int		j;

	if (!(res = (t_file ***)malloc(sizeof(t_file **) * command_line->autocompletion.nb_lines)))
		return (NULL);
	i = 0;
	while (i < command_line->autocompletion.nb_lines)
	{
		if (!(res[i] = (t_file **)malloc(sizeof(t_file *) * command_line->autocompletion.nb_cols)))
		{
			while (i--)
				free(res[i]);
			free(res);
			return (NULL);
		}
		j = 0;
		while (j < command_line->autocompletion.nb_cols)
		{
			res[i][j] = NULL;
			j++;
		}
		i++;
	}
	fill_file_tables(command_line, res);
	return (res);
}

void	fill_buffer_padding(char **print_buffer)
{
	int i;

	i = 0;
	while (i < AC_PADDING)
	{
		ft_strcpy(*print_buffer, " ");
		(*print_buffer)++;
		i++;
	}
}

void	fill_buffer_from_file(t_command_line *command_line, char **print_buffer,
			t_file *file, int max_len)
{
	int		i;
	char	*str;
	int		is_current;

	str = tgetstr("mr", NULL);
	i = 0;
	if (file)
	{
		is_current = command_line->autocompletion.head
			&& file == command_line->autocompletion.head->content;
		if (is_current)
		{
			ft_strcpy(*print_buffer, str);
			*print_buffer += ft_strlen(str);
		}
		else if (S_ISDIR(file->st.st_mode))
		{
			ft_strcpy(*print_buffer, DIR_COLOR);
			*print_buffer += ft_strlen(DIR_COLOR);
		}
		ft_strcpy(*print_buffer, file->name);
		i = ft_strlen(file->name);
		*print_buffer += i;
		if (S_ISDIR(file->st.st_mode))
		{
			if (!is_current)
			{
				ft_strcpy(*print_buffer, EOC);
				*print_buffer += ft_strlen(EOC);
			}
			ft_strcpy(*print_buffer, BOLD"/");
			*print_buffer += ft_strlen(BOLD"/");
			if (!is_current)
			{
				ft_strcpy(*print_buffer, EOC);
				*print_buffer += ft_strlen(EOC);
			}
			i++;
		}
	}
	while (command_line->autocompletion.nb_cols > 1 && i < max_len)
	{
		ft_strcpy(*print_buffer, " ");
		(*print_buffer)++;
		i++;
	}
	if (is_current)
	{
		ft_strcpy(*print_buffer, EOC);
		*print_buffer += ft_strlen(EOC);
	}
}

void	fill_buffer_from_tables(t_command_line *command_line,
			char *print_buffer, t_file ***tbl, int max_len)
{
	int		i;
	int		j;

	i = 0;
	while (i < command_line->autocompletion.nb_lines)
	{
		j = 0;
		while (j < command_line->autocompletion.nb_cols)
		{
			fill_buffer_from_file(command_line,
				&print_buffer, tbl[i][j], max_len);
			j++;
			if (j < command_line->autocompletion.nb_cols)
				fill_buffer_padding(&print_buffer);
		}
		i++;
		if (i < command_line->autocompletion.nb_lines)
		{
			ft_strcpy(print_buffer, "\n");
			print_buffer += 1;
		}
	}
}
void	fill_buffer_partial_from_tables(t_command_line *command_line,
			char *print_buffer, t_file ***tbl, int max_len)
{
	int		i;
	int		j;
	int		limit;

	i = command_line->autocompletion.scrolled_lines;
	while (i <= (limit = command_line->autocompletion.scrolled_lines
			+ g_glob.winsize.ws_row - 1 - command_line_nb_rows(command_line)))
	{
		j = 0;
		while (j < command_line->autocompletion.nb_cols)
		{
			fill_buffer_from_file(command_line,
				&print_buffer, tbl[i][j], max_len);
			j++;
			if (j < command_line->autocompletion.nb_cols)
				fill_buffer_padding(&print_buffer);
		}
		i++;
		if (i != limit + 1)
		{
			ft_strcpy(print_buffer, "\n");
			print_buffer += 1;
		}
	}
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

int		render_choices(t_command_line *command_line)
{
	char	*print_buffer;
	int		max_len;
	int		nb_visible_lines;
	t_file	***tbl;

	max_len = sh_get_max_file_len(command_line->autocompletion.choices);
	command_line->autocompletion.nb_cols = ft_max(1, 
		(g_glob.winsize.ws_col + AC_PADDING) / (max_len + AC_PADDING));
	command_line->autocompletion.nb_lines = ft_max(1,
		ft_round((double)ft_dlstlength(command_line->autocompletion.choices)
			/ (double)command_line->autocompletion.nb_cols));
	tbl = update_file_tables(command_line);
	command_line->autocompletion.nb_cols = ft_max(1,
		ft_round((double)ft_dlstlength(command_line->autocompletion.choices)
			/ (double)command_line->autocompletion.nb_lines));
	if (!(print_buffer = ft_strnew((g_glob.winsize.ws_col * g_glob.winsize.ws_row) * (4 + (2 * ft_strlen(EOC) + ft_strlen(DIR_COLOR))))))
		return (1);
	nb_visible_lines = command_line_visible_lines(command_line);
	if (nb_visible_lines + command_line_nb_rows(command_line) > g_glob.winsize.ws_row)
		fill_buffer_partial_from_tables(command_line, print_buffer, tbl, max_len);
	else
		fill_buffer_from_tables(command_line, print_buffer, tbl, max_len);
	ft_dprintf(0, print_buffer);
	go_up_left(nb_visible_lines);
	free_tbl(tbl, command_line->autocompletion.nb_lines);
	usleep(10000);
	return (ft_free_turn(print_buffer, SUCCESS));
}
