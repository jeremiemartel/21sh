/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:27:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/21 15:21:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_ctrl_c(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.head = NULL;
	command_line->autocompletion.active = 0;
	if (command_line->searcher.active == 0)
	{
		get_down_from_command(command_line);
		reset_command_line(shell, command_line);
	}
	command_line->searcher.active = 0;
	shell->ret_value_set = 0;
	if (sh_env_update_ret_value_and_question(shell, SH_RET_CTRL_C))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (CTRL_C);
}

int		process_ctrl_d(t_shell *shell, t_command_line *command_line)
{
	if (command_line->dy_str->current_size == 0
			&& (command_line->context == E_CONTEXT_STANDARD
				|| command_line->context == E_CONTEXT_HEREDOC
					|| command_line->context == E_CONTEXT_BACKSLASH))
	{
		if (command_line->context == E_CONTEXT_STANDARD
			|| command_line->context == E_CONTEXT_BACKSLASH)
			shell->running = 0;
		return (CTRL_D);
	}
	else
		ring_bell();
	return (KEEP_READ);
}
