/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:45:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 16:55:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_true_cursor_pos(int cursor)
{
	return (cursor + ft_strlen(PROMPT));
}

void	get_down_from_command(t_command_line *command_line)
{
	int		full_y;
	int		cursor_y;
	int		i;
	char	*str;

	full_y = get_true_cursor_pos(command_line->nb_chars) / g_glob.winsize.ws_col;
	cursor_y = get_true_cursor_pos(g_glob.cursor) / g_glob.winsize.ws_col;
	str = tgetstr("do", NULL);
	i = cursor_y;
	while (i < full_y)
	{
		tputs(str, 1, putchar_int);
		i++;
	}
	tputs(str, 1, putchar_int);
}

void	go_up_to_prompt(int width, int cursor)
{
	char		*str;
	int			val;
	int			i;

	str = tgetstr("up", NULL);
	i = 0;
	ft_dprintf(0, " ");
	val = ((get_true_cursor_pos(cursor)) / width);
	while (i < val)
	{
		tputs(str, 1, putchar_int);
		i++;
	}
	str = tgetstr("cr", NULL);
	tputs(str, 1, putchar_int);
}

void	replace_cursor_after_render(void)
{
	char	*str;
	int		x;
	int		y;

	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.command_line.nb_chars);
	y = (get_true_cursor_pos(g_glob.cursor)) / g_glob.winsize.ws_col;
	x = (get_true_cursor_pos(g_glob.cursor)) % g_glob.winsize.ws_col;
	str = tgetstr("do", NULL);
	while (y--)
		tputs(str, 1, putchar_int);
	str = tgetstr("nd", NULL);
	while (x--)
		tputs(str, 1, putchar_int);
}

int		process_clear(t_dy_str *dy_str)
{
	char *str;

	str = tgetstr("cl", NULL);
	tputs(str, 1, putchar_int);
	render_command_line(dy_str, 0);
	return (0);
}
