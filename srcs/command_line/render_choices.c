/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 13:53:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
		if ((ret = ft_strlen_utf8(file->name)
				+ S_ISDIR(file->st.st_mode)) > max)
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

void	render_choices(t_command_line *command_line)
{
	t_dlist	*ptr;
	t_file	*file;
	int     first;
	int		max_len;
	int		i;
	int		j;

	max_len = sh_get_max_file_len(command_line->autocompletion.choices);
	command_line->autocompletion.nb_cols = ft_max(1, (g_glob.winsize.ws_col + AC_PADDING) / (max_len + AC_PADDING));
	command_line->autocompletion.nb_lines = ft_max(1, ft_round((double)ft_dlstlength(command_line->autocompletion.choices) / (double)command_line->autocompletion.nb_cols));
	if (command_line->autocompletion.nb_lines + 1 + 1 > g_glob.winsize.ws_row) //replace 1 by nbrows of commandline
		render_choices_partial(command_line, max_len);
	else
	{
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
			render_file(command_line, file, max_len, j);
			ptr = ptr->next;
			first = 0;
			if (++i == command_line->autocompletion.nb_lines)
			{
				go_up_left(i);
				i = 0;
				j++;
			}
		}
		go_up_left(i + 1);
	}
}
