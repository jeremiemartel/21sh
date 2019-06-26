/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:58:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		update_prompt_from_absolute_path(char *cwd, char **new_prompt)
{
	char	*path;

	if (get_path_from_absolute_path(cwd, &path))
	{
		free(cwd);
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
	}
	free(cwd);
	if (!(*new_prompt = ft_strjoin_free(*new_prompt, path, 1)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
	free(path);
	return (SUCCESS);
}

int		update_prompt_cwd(t_shell *shell, char **new_prompt)
{
	char	*cwd;
	char	*home;

	if (!(*new_prompt = ft_strdup("→ ")))
		return (sh_perror("cwd error", "update_prompt_cwd"));
	if (!(cwd = getcwd(NULL, 0)))
		return (ft_free_turn(*new_prompt, sh_perror("cwd error", "cwd")));
	if (!(home = get_home_dup(shell)))
	{
		free(*new_prompt);
		free(cwd);
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
	}
	if (!ft_strcmp(home, cwd))
	{
		free(cwd);
		free(home);
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, "~", 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd"));
		return (SUCCESS);
	}
	free(home);
	return (update_prompt_from_absolute_path(cwd, new_prompt));
}

int		update_prompt_context(t_shell *shell, t_command_line *command_line,
			char **new_prompt)
{
	if (command_line->context == E_CONTEXT_STANDARD)
	{
		if (update_prompt_cwd(shell, new_prompt))
			return (1);
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_HEREDOC)
	{
		if (!(*new_prompt = ft_strdup(HEREDOC_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_QUOTE)
	{
		if (!(*new_prompt = ft_strdup(QUOTE_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_DQUOTE)
	{
		if (!(*new_prompt = ft_strdup(DQUOTE_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (!(*new_prompt = ft_strdup(BACKSLASH_PROMPT)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	return (SUCCESS);
}

int		update_prompt(t_shell *shell, t_command_line *command_line)
{
	char *new_prompt;

	ft_strdel(&command_line->prompt);
	if (update_prompt_context(shell, command_line, &new_prompt))
		return (FAILURE);
	if (command_line->mode == E_MODE_VISUAL)
	{
		if (!(new_prompt = ft_strjoin_free(new_prompt, VISUAL_PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->mode == E_MODE_COMMAND)
	{
		if (!(new_prompt = ft_strjoin_free(new_prompt, COMMAND_PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	if (command_line->context != E_CONTEXT_STANDARD)
	{
		if (!(new_prompt = ft_strjoin_free(new_prompt, PROMPT_SUFFIX, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (!(new_prompt = ft_strjoin_free(new_prompt, " ", 1)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
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
