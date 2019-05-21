/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:58:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 14:06:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	switch_prompt(t_command_line *command_line, char *new_prompt)
{
	free(command_line->prompt);
	command_line->prompt = new_prompt;
	render_command_line(command_line, 0, 1);
}

int		process_escape(t_command_line *command_line)
{
	char *new_prompt;

	if (!(new_prompt = ft_strdup(COMMAND_PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "process_escape"));
	command_line->autocompletion.active = 0;
	command_line->autocompletion.head = NULL;
	switch_prompt(command_line, new_prompt);
	command_line->mode = E_MODE_COMMAND;
	return (SUCCESS);
}

int		process_i(t_command_line *command_line)
{
	char *new_prompt;

	if (!(new_prompt = ft_strdup(PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "process_i"));
	switch_prompt(command_line, new_prompt);
	command_line->mode = E_MODE_INSERT;
	return (SUCCESS);
}

int		process_v(t_command_line *command_line)
{
	char *new_prompt;

	if (!(new_prompt = ft_strdup(VISUAL_PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "process_v"));
	switch_prompt(command_line, new_prompt);
	command_line->mode = E_MODE_VISUAL;
	command_line->pinned_index = command_line->current_index;
	return (SUCCESS);
}
