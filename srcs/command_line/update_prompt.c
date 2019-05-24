/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:58:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/24 11:02:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		update_prompt_cwd(t_shell *shell, char **new_prompt)
{
	char	*cwd;
	char	*path;
	char	*home;

	if (!(*new_prompt = ft_strdup("→ ")))
		return (ft_perror("cwd error", "update_prompt_cwd"));
	if (!(cwd = getcwd(NULL, 0)))
		return (ft_perror("cwd error", "update_prompt_cwd"));
	if (!(home = get_home_dup(shell)))
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
	if (!ft_strcmp(home, cwd))
	{
		free(cwd);
		free(home);
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, "~", 1)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
		return (SUCCESS);
	}
	if (get_path_from_absolute_path(cwd, &path))
	{
		free(cwd);
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
	}
	free(cwd);
	if (!(*new_prompt = ft_strjoin_free(*new_prompt, path, 1)))
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
	return (SUCCESS);
}

int		update_prompt_context(t_shell *shell, t_command_line *command_line,
			char **new_prompt)
{
	if (command_line->context == E_CONTEXT_STANDARD)
	{
		if (update_prompt_cwd(shell, new_prompt))
			return (FAILURE);
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, PROMPT, 1)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_HEREDOC)
	{
		if (!(*new_prompt = ft_strdup(HEREDOC_PROMPT)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_QUOTE)
	{
		if (!(*new_prompt = ft_strdup(QUOTE_PROMPT)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_DQUOTE)
	{
		if (!(*new_prompt = ft_strdup(DQUOTE_PROMPT)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (!(*new_prompt = ft_strdup(BACKSLASH_PROMPT)))
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	return (SUCCESS);
}

int		update_prompt(t_shell *shell, t_command_line *command_line)
{
	char *new_prompt;

	if (command_line->prompt)
		free(command_line->prompt);
	if (update_prompt_context(shell, command_line, &new_prompt))
		return (FAILURE);
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
	if (command_line->context != E_CONTEXT_STANDARD)
	{
		if (!(new_prompt = ft_strjoin_free(new_prompt, PROMPT_SUFFIX, 1)))
			return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (!(new_prompt = ft_strjoin_free(new_prompt, " ", 1)))
		return (ft_perror(SH_ERR1_MALLOC, "update_prompt"));
	command_line->prompt = new_prompt;
	return (SUCCESS);
}

int		update_prompt_from_quote(t_shell *shell, t_command_line *command_line,
			char quote)
{
	if (quote == '\'')
		command_line->context = E_CONTEXT_QUOTE;
	else if (quote == '\"')
		command_line->context = E_CONTEXT_DQUOTE;
	else if (quote == '\\')
		command_line->context = E_CONTEXT_BACKSLASH;
	return (update_prompt(shell, command_line));
}

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
