/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:49:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 02:49:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_escape(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.active = 0;
	command_line->autocompletion.head = NULL;
	command_line->mode = E_MODE_COMMAND;
	if (update_prompt(shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}

int		process_i(t_shell *shell, t_command_line *command_line)
{
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}

int		process_v(t_shell *shell, t_command_line *command_line)
{
	command_line->mode = E_MODE_VISUAL;
	command_line->pinned_index = command_line->current_index;
	if (update_prompt(shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}
