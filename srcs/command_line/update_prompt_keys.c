/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:49:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/05 14:17:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		update_prompt_cwd_home(char **new_prompt)
{
	if (!(*new_prompt = ft_strjoin_free(*new_prompt, "~", 1)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd_home"));
	return (SUCCESS);
}

int		process_escape(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.active = 0;
	command_line->autocompletion.head = NULL;
	command_line->searcher.active = 0;
	command_line->mode = E_MODE_COMMAND;
	if (update_prompt(shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}

int		process_i(t_shell *shell, t_command_line *command_line,
			t_key_buffer *buffer)
{
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	flush_keys(buffer);
	return (SUCCESS);
}

int		process_v(t_shell *shell, t_command_line *command_line,
			t_key_buffer *buffer)
{
	command_line->mode = E_MODE_VISUAL;
	command_line->pinned_index = command_line->current_index;
	if (update_prompt(shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	flush_keys(buffer);
	return (SUCCESS);
}
