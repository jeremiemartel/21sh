/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:33:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 14:33:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_true_cursor_pos(int cursor)
{
	return (cursor + ft_strlen(g_glob.command_line.prompt));
}

int		get_down_from_command(t_command_line *command_line)
{
	int		full_y;
	int		cursor_y;
	int		i;
	char	*str;
	int		ret;

	ret = 0;
	full_y = get_true_cursor_pos(command_line->nb_chars) / g_glob.winsize.ws_col;
	cursor_y = get_true_cursor_pos(g_glob.cursor) / g_glob.winsize.ws_col;
	str = tgetstr("do", NULL);
	i = cursor_y;
	while (i < full_y)
	{
		tputs(str, 1, putchar_int);
		i++;
		ret++;
	}
	tputs(str, 1, putchar_int);
	return (ret);
}

void	replace_cursor_on_index()
{
	char	*str;
	int		x;
	int		y;

	y = (get_true_cursor_pos(g_glob.cursor)) / g_glob.winsize.ws_col;
	x = (get_true_cursor_pos(g_glob.cursor)) % g_glob.winsize.ws_col;
	str = tgetstr("do", NULL);
	while (y--)
		tputs(str, 1, putchar_int);
	str = tgetstr("nd", NULL);
	while (x--)
		tputs(str, 1, putchar_int);
}

void	replace_cursor_after_render(void)
{
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.command_line.nb_chars);
	replace_cursor_on_index();
}

int		process_clear(t_command_line *command_line)
{
	char *str;

	str = tgetstr("cl", NULL);
	tputs(str, 1, putchar_int);
	render_command_line(command_line, 0);
	return (0);
}
