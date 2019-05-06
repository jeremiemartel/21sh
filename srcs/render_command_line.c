/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/06 18:36:07 by ldedier          ###   ########.fr       */
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
		if ((ret = ft_strlen_utf8(file->name)) > max)
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
		ft_printf(DIR_COLOR);
	ft_printf("%s", file->name);
	str = tgetstr("me", NULL);
	tputs(str, 1, putchar_int);
	str = tgetstr("do", NULL);
	tputs(str, 1, putchar_int);
	return (0);
}

static int	render_choices_partial(t_command_line *command_line, int max_len, int nb_lines)
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
		if (i >= command_line->autocompletion.scrolled_lines && i <= command_line->autocompletion.scrolled_lines + g_glob.winsize.ws_row - 3)
			render_file(command_line, file, max_len, j);
		ptr = ptr->next;
		first = 0;
		if (i++ == nb_lines)
		{
			go_up_left(g_glob.winsize.ws_row - (2));
			i = 0;
			j++;
		}
	}
	go_up_left(ft_min(i + 1, g_glob.winsize.ws_row - (1)));
	return (0);
}

static int	render_choices(t_command_line *command_line, int to_go_up)
{
	t_dlist	*ptr;
	t_file	*file;
	int     first;
	int		max_len;
	int		nb_cols;
	int		nb_lines;
	int		i;
	int		j;

	(void)to_go_up;
	max_len = sh_get_max_file_len(command_line->autocompletion.choices);
	nb_cols = ft_max(1, (g_glob.winsize.ws_col + AC_PADDING)
				/ (max_len + AC_PADDING));
	nb_lines = ft_dlstlength(command_line->autocompletion.choices) / nb_cols;
	if (nb_lines + 1 + 1 > g_glob.winsize.ws_row) //replace 1 by nbrows of commandline
	{
		render_choices_partial(command_line, max_len, nb_lines);
	}
	else
	{
		//	ft_printf("%d cols, %d lines \n", nb_cols,  nb_lines);
		ptr = command_line->autocompletion.choices;
		first = 1;
		i = 0;
		j = 0;
		while ((ptr != command_line->autocompletion.choices
					&& ptr != NULL) || (first && ptr != NULL))
		{
			file = (t_file *)ptr->content;
			render_file(command_line, file, max_len, j);
			//	ft_printf("%s\n", file->name);
			ptr = ptr->next;
			first = 0;
			if (i++ == nb_lines)
			{
				go_up_left(i);
				i = 0;
				j++;
			}
		}
		go_up_left(i + 1);
	}
	return (0);
}

/*
** cursor_inc: tells the cursor movement to execute within the render of the
** command_line
*/

int		render_command_line(t_command_line *command_line, int cursor_inc)
{
	char	*str;
	int		to_go_up;

	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.cursor);
	str = tgetstr("cd", NULL);
	tputs(str, 1, putchar_int);
	ft_dprintf(0, "%s%s%s%s", BOLD, CYAN, g_glob.command_line.prompt, EOC);
	ft_dprintf(0, "%s", command_line->dy_str->str);
	g_glob.cursor += cursor_inc;
	replace_cursor_after_render();
	if (command_line->autocompletion.active)
	{
		to_go_up = get_down_from_command(command_line);
		render_choices(command_line, to_go_up);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	return (0);
}
