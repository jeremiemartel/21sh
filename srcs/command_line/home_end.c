/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:42:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/09 14:48:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_end(t_command_line *command_line)
{
	command_line->current_index = command_line->dy_str->current_size;
	render_command_line(command_line, command_line->nb_chars - g_glob.cursor, 1);
	return (SUCCESS);
}

int		process_start(t_command_line *command_line)
{
	command_line->current_index = 0;
	render_command_line(command_line, - g_glob.cursor, 1);
	return (SUCCESS);
}
