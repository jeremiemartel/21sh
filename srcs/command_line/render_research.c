/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 19:54:46 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/20 19:54:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		render_research(t_command_line *command_line)
{
	int		nb_visible_lines;
	char	title[100];

	if (command_line->searcher.unsuccessful == 0)
		ft_strcpy(title, UNSUCCESS_RSRCH);
	else
		ft_strcpy(title, SUCCESS_RSRCH);
	ft_printf("%s%s_", title, command_line->searcher.dy_str->str);
	nb_visible_lines = ((ft_strlen_utf8(command_line->searcher.dy_str->str)
		+ ft_strlen(title) + 1) - 1) / g_glob.winsize.ws_col;
	go_up_left(nb_visible_lines);
	return (SUCCESS);
}
