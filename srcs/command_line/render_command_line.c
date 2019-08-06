/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/13 18:36:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	render_command_researched(t_command_line *command_line)
{
	int		len;
	char	*str;

	ft_putnstr_fd(command_line->dy_str->str,
		command_line->searcher.match_index, 0);
	str = tgetstr("us", NULL);
	tputs(str, 1, putchar_int);
	ft_putstr_fd(command_line->searcher.dy_str->str, 0);
	str = tgetstr("ue", NULL);
	tputs(str, 1, putchar_int);
	len = ft_strlen(command_line->searcher.dy_str->str);
	ft_putstr_fd(&command_line->dy_str->str[command_line->searcher.match_index
		+ len], 0);
}

int		print_after_command_line(t_command_line *command_line,
		int print_choices)
{
	int to_go_up;

	if (print_choices && command_line->autocompletion.active)
	{
		to_go_up = get_down_from_command(command_line);
		render_choices(command_line);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	else if (command_line->searcher.active)
	{
		to_go_up = get_down_from_command(command_line);
		if (render_research(command_line))
			return (FAILURE);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	return (SUCCESS);
}

/*
** cursor_inc: tells the cursor movement to execute within the render of the
** command_line
*/

int		render_command_line(t_command_line *command_line,
			int cursor_inc, int print_choices)
{
	char	*str;

	if (!isatty(0) || !command_line)
		return (SUCCESS);
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.cursor);
	str = tgetstr("cd", NULL);
	tputs(str, 1, putchar_int);
	ft_dprintf(0, "%s%s%s%s", BOLD, CYAN, g_glob.command_line.prompt, EOC);
	if (command_line->mode == E_MODE_VISUAL)
		render_command_visual(command_line);
	else if (command_line->searcher.active
			&& !command_line->searcher.unsuccessful
				&& ft_strcmp(command_line->searcher.dy_str->str, ""))
		render_command_researched(command_line);
	else
		ft_dprintf(0, "%s", command_line->dy_str->str);
	g_glob.cursor += cursor_inc;
	replace_cursor_after_render();
	if (print_after_command_line(command_line, print_choices) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
