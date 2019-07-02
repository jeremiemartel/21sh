/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:14:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/03 00:12:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	heredoc_ret(t_shell *shell, t_command_line *command_line, int ret)
{
	command_line->context = E_CONTEXT_STANDARD;
	update_prompt(shell, command_line);
	return (ret);
}

static char	*heredoc_ret_str(t_shell *shell,
			t_command_line *command_line, char *str)
{
	command_line->context = E_CONTEXT_STANDARD;
	update_prompt(shell, command_line);
	return (str);
}

int			process_heredoc_through_command(char **res, t_shell *shell,
	t_heredoc_func heredoc_func, t_command_line *command_line)
{
	char	*tmp;

	if (!(tmp = heredoc_func(command_line->dy_str->str)))
		return (heredoc_ret(shell, command_line, FAILURE));
	if (!ft_strcmp(tmp, command_line->heredoc_eof))
	{
		free(tmp);
		return (heredoc_ret(shell, command_line, SUCCESS));
	}
	else
	{
		if (!(*res = ft_strjoin_free(*res, tmp, 3)))
			return (heredoc_ret(shell, command_line, FAILURE));
		if (!(*res = ft_strjoin_free(*res, "\n", 1)))
			return (heredoc_ret(shell, command_line, FAILURE));
	}
	return (3);
}

void		init_heredoc_command_line(t_shell *shell,
				t_command_line *command_line, char *stop)
{
	command_line->heredoc_eof = stop;
	flush_command_line(command_line);
	render_command_line(command_line, -g_glob.cursor, 1);
	command_line->context = E_CONTEXT_HEREDOC;
	update_prompt(shell, command_line);
}

char		*heredoc(t_shell *shell, char *stop,
			t_heredoc_func heredoc_func, int *ret)
{
	char			*res;
	t_command_line	*command_line;

	command_line = &g_glob.command_line;
	init_heredoc_command_line(shell, command_line, stop);
	if (!(res = ft_strnew(0)))
		return (heredoc_ret_str(shell, command_line, NULL));
	while ((*ret = sh_get_command(shell, command_line)) == SUCCESS)
	{
		if (process_heredoc_through_command(&res, shell, heredoc_func,
			command_line) != 3)
			return (res);
	}
	if (*ret == CTRL_D)
		return (heredoc_ret_str(shell, command_line, res));
	else
	{
		free(res);
		return (heredoc_ret_str(shell, command_line, NULL));
	}
}
