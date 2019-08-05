/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_insert_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:09:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/05 15:18:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_enter_no_autocompletion(t_command_line *command_line)
{
	command_line->autocompletion.active = 0;
	command_line->searcher.active = 0;
	render_command_line(command_line, 0, 0);
	get_down_from_command(command_line);
	command_line->dy_str->current_size = 0;
	return (0);
}

void	cancel_autocompletion(t_key_buffer *buffer,
				t_command_line *command_line)
{
	if ((buffer->progress == 1 &&
		(buffer->buff[0] != 10 && buffer->buff[0] != 9
		&& buffer->buff[0] != 27))
			|| (buffer->progress == 2 &&
				(buffer->buff[1] != 91 && buffer->buff[1] != 79))
				|| (buffer->progress == 3 &&
					(buffer->buff[2] < 65 || buffer->buff[2] > 68)))
	{
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
	}
}
