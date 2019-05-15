/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/13 18:31:12 by ldedier          ###   ########.fr       */
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

static int	render_file(t_command_line *command_line, t_file *file, int max_len, int column)
{
	char *str;
	int is_current;

	is_current = command_line->autocompletion.head
		&& file == command_line->autocompletion.head->content;
	go_right(column * (AC_PADDING + max_len));
	str = tgetstr("mr", NULL);
	if (is_current)
		tputs(str, 1, putchar_int);
	if (S_ISDIR(file->st.st_mode) && !is_current)
		ft_dprintf(0, DIR_COLOR);
	ft_dprintf(0, "%s", file->name);
	str = tgetstr("me", NULL);
	ft_printf("%s", EOC);
	if (S_ISDIR(file->st.st_mode))
		ft_dprintf(0, BOLD"/");
	tputs(str, 1, putchar_int);
	str = tgetstr("do", NULL);
	tputs(str, 1, putchar_int);
	return (0);
}

static int	render_choices_partial(t_command_line *command_line, int max_len)
{
	t_dlist	*ptr;
	int first;
	int i;
	int j;
	t_file *file;

	ptr = command_line->autocompletion.choices;
	first = 1;
	i = 0;
	j = 0;
	while ((ptr != command_line->autocompletion.choices
		&& ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		file->y = i;
		file->x = j;
		if (i >= command_line->autocompletion.scrolled_lines
			&& i <= command_line->autocompletion.scrolled_lines + g_glob.winsize.ws_row - 3)
			render_file(command_line, file, max_len, j);
		ptr = ptr->next;
		first = 0;
		if (++i == command_line->autocompletion.nb_lines)
		{
			go_up_left(g_glob.winsize.ws_row - (2));
			i = 0;
			j++;
		}
	}
	go_up_left(ft_min(i + 1, g_glob.winsize.ws_row - (1)));
	return (0);
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

void	render_choices(t_command_line *command_line)
{
	t_dlist	*ptr;
	t_file	*file;
	int     first;
	int		max_len;
	int		i;
	int		j;
	int		nb_visible_lines;
	int		rendered_lines;

	max_len = sh_get_max_file_len(command_line->autocompletion.choices);
	command_line->autocompletion.nb_cols = ft_max(1, (g_glob.winsize.ws_col + AC_PADDING) / (max_len + AC_PADDING));	
	command_line->autocompletion.nb_lines = ft_max(1, ft_round((double)ft_dlstlength(command_line->autocompletion.choices) / (double)command_line->autocompletion.nb_cols));
	nb_visible_lines = command_line_visible_lines(command_line);

	if (nb_visible_lines + command_line_nb_rows(command_line) + 1 > g_glob.winsize.ws_row)
		render_choices_partial(command_line, max_len);
	else
	{
		ptr = command_line->autocompletion.choices;
		first = 1;
		i = 0;
		j = 0;
		rendered_lines = 0;
		while ((ptr != command_line->autocompletion.choices
					&& ptr != NULL) || (first && ptr != NULL))
		{
			file = (t_file *)ptr->content;
			file->y = i;
			file->x = j;
			render_file(command_line, file, max_len, j);
			rendered_lines += lines_rendered_from_file(file);
			ptr = ptr->next;
			first = 0;
			if (++i == command_line->autocompletion.nb_lines)
			{
			//	sleep(1);
				go_up_left(nb_visible_lines);
			//	sleep(1);
				i = 0;
				j++;
				rendered_lines = 0;
			}
		}
		go_up_left(rendered_lines + 1);
	}
}
