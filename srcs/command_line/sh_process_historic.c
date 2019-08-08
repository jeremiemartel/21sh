/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_historic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:44:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/07 18:18:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	update_command_line(t_command_line *command_line)
{
	command_line->current_index = command_line->dy_str->current_size;
	command_line->nb_chars = ft_strlen_utf8(command_line->dy_str->str);
}

int			process_historic_down(t_shell *shell, t_command_line *command_line)
{
	char *str;

	if (!shell->historic.head->prev)
		return (SUCCESS);
	if (shell->historic.head == shell->historic.commands)
	{
		shell->historic.head = &shell->historic.head_start;
		if (ft_strcmp(command_line->dy_str->str, ""))
		{
			flush_command_line(command_line);
			update_command_line(command_line);
			render_command_line(command_line,
				command_line->nb_chars - g_glob.cursor, 1);
		}
		return (SUCCESS);
	}
	shell->historic.head = shell->historic.head->prev;
	str = (char *)shell->historic.head->content;
	flush_command_line(command_line);
	if (ft_dy_str_cpy_str(command_line->dy_str, str))
		return (FAILURE);
	update_command_line(command_line);
	render_command_line(command_line,
		command_line->nb_chars - g_glob.cursor, 1);
	return (SUCCESS);
}

int			process_historic_up(t_shell *shell, t_command_line *command_line)
{
	char *str;

	if (!shell->historic.commands)
		return (SUCCESS);
	if (shell->historic.head->next == shell->historic.commands
		&& shell->historic.head != &shell->historic.head_start)
		return (SUCCESS);
	shell->historic.head = shell->historic.head->next;
	str = (char *)shell->historic.head->content;
	flush_command_line(command_line);
	if (ft_dy_str_cpy_str(command_line->dy_str, str))
		return (FAILURE);
	update_command_line(command_line);
	render_command_line(command_line,
		command_line->nb_chars - g_glob.cursor, 1);
	return (SUCCESS);
}
