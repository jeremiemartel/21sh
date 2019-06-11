/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_choices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 02:33:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*new_print_buffer(void)
{
	return (ft_strnew((g_glob.winsize.ws_col * g_glob.winsize.ws_row)
			* (4 + (2 * ft_strlen(EOC) + ft_strlen(DIR_COLOR)))));
}

int		sh_should_render_choices(t_command_line *command_line,
			int nb_visible_lines)
{
	return (command_line->autocompletion.nb_cols != 1
			|| nb_visible_lines
				+ command_line_nb_rows(command_line) <= g_glob.winsize.ws_row);
}

void	update_dimensions(t_command_line *command_line, int max_len)
{
	command_line->autocompletion.nb_cols = ft_max(1,
		(g_glob.winsize.ws_col + AC_PADDING) / (max_len + AC_PADDING));
	command_line->autocompletion.nb_lines = ft_max(1,
		ft_round((double)ft_dlstlength(command_line->autocompletion.choices)
			/ (double)command_line->autocompletion.nb_cols));
}

void	update_back_nb_cols(t_command_line *command_line)
{
	command_line->autocompletion.nb_cols = ft_max(1,
		ft_round((double)ft_dlstlength(command_line->autocompletion.choices)
			/ (double)command_line->autocompletion.nb_lines));
}

int		render_choices(t_command_line *command_line)
{
	char	*print_buffer;
	int		max_len;
	int		nb_visible_lines;
	t_file	***tbl;

	max_len = sh_get_max_file_len(command_line->autocompletion.choices);
	update_dimensions(command_line, max_len);
	tbl = update_file_tables(command_line);
	update_back_nb_cols(command_line);
	nb_visible_lines = command_line_visible_lines(command_line);
	if (!sh_should_render_choices(command_line, nb_visible_lines))
		return (SUCCESS);
	if (!(print_buffer = new_print_buffer()))
		return (sh_perror(SH_ERR1_MALLOC, "render_choices"));
	if (nb_visible_lines + command_line_nb_rows(command_line)
			> g_glob.winsize.ws_row)
		fill_buffer_partial_from_tables(command_line,
			print_buffer, tbl, max_len);
	else
		fill_buffer_from_tables(command_line, print_buffer, tbl, max_len);
	ft_dprintf(0, print_buffer);
	go_up_left(nb_visible_lines - 1);
	free_tbl(tbl, command_line->autocompletion.nb_lines);
	return (ft_free_turn(print_buffer, SUCCESS));
}
