/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/22 17:19:33 by ldedier          ###   ########.fr       */
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


static int	render_file(t_file *file, int max_len, int column)
{
	char *str;

	go_right(column * (AC_PADDING + max_len));
	ft_printf("%s", file->name);
	str = tgetstr("do", NULL);
	tputs(str, 1, putchar_int);
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
//	ft_printf("%d cols, %d lines \n", nb_cols,  nb_lines);
	ptr = command_line->autocompletion.choices;
	first = 1;
	i = 0;
	j = 0;
	while ((ptr != command_line->autocompletion.choices
			&& ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		render_file(file, max_len, j);
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
	if (command_line->autocompletion.head)
	{
		to_go_up = get_down_from_command(command_line);
		render_choices(command_line, to_go_up);
	}
	return (0);
}
