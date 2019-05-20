/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:58:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/20 18:05:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		update_prompt(t_command_line *command_line)
{
	char *new_prompt;

	free(command_line->prompt);
	if (command_line->context == E_CONTEXT_STANDARD)
	{
		if (!(new_prompt = ft_strdup(PROMPT)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (!(new_prompt = ft_strdup(HEREDOC_PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	if (command_line->mode == E_MODE_VISUAL)
	{
		if (!(new_prompt = ft_strjoin_free(new_prompt, VISUAL_PROMPT, 1)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->mode == E_MODE_COMMAND)
	{
		if (!(new_prompt = ft_strjoin_free(new_prompt, COMMAND_PROMPT, 1)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	if (!(new_prompt = ft_strjoin_free(new_prompt, PROMPT_SUFFIX, 1)))
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	command_line->prompt = new_prompt;
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}

int		process_escape(t_command_line *command_line)
{
	command_line->autocompletion.active = 0;
	command_line->autocompletion.head = NULL;
	command_line->mode = E_MODE_COMMAND;
	if (update_prompt(command_line))
		return (FAILURE);
	return (SUCCESS);
}

int		process_i(t_command_line *command_line)
{
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line))
		return (FAILURE);
	return (SUCCESS);
}

int		process_v(t_command_line *command_line)
{
	command_line->mode = E_MODE_VISUAL;
	command_line->pinned_index = command_line->current_index;
	if (update_prompt(command_line))
		return (FAILURE);
	return (SUCCESS);
}
