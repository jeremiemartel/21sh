/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:14:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 14:36:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** reduces matching \\ into a single one, returns 1 if str ends up with
** a single \ and removes it from the string, else returns 0
*/
int			refine_heredoc(char *str)
{
	int		i;
	int		n;

	i = 0;
	while (str[i])
	{
		if (!str[i + 1] && str[i] == '\\')
		{
			str[i] = '\0';
			return (1);
		}
		if (str[i + 1] == '\\' && str[i] == '\\')
		{
			n = 0;
			while (str[i + n + 1])
			{
				str[i + n] = str[i + n + 1];
				n++;
			}
			str[i + n] = '\0';
		}
		i++;
	}
	return (0);
}

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

int		append_to_str(char **str, char *to_append)
{
	if (*str == NULL)
	{
		if (!(*str = ft_strdup(to_append)))
			return (1);
	}
	else if (!(*str = ft_strjoin_free(*str, to_append, 1)))
		return (1);
	return (0);
}

int			process_heredoc_new_line(char **res, char *tmp, t_shell *shell,
				t_command_line *command_line)
{
	char *to_compare;

	if (!(to_compare = command_line->to_append_str ?
			ft_strjoin(command_line->to_append_str, tmp) : ft_strdup(tmp)))
	{
		free(tmp);
		ft_strdel(&command_line->to_append_str);
		return (heredoc_ret(shell, command_line, FAILURE));
	}
	free(tmp);
	if (!ft_strcmp(to_compare, command_line->heredoc_eof))
	{
		free(to_compare);
		ft_strdel(&command_line->to_append_str);
		return (heredoc_ret(shell, command_line, SUCCESS));
	}
	else
	{
		ft_strdel(&command_line->to_append_str);
		if (!(*res = ft_strjoin_free(*res, to_compare, 3)))
			return (heredoc_ret(shell, command_line, FAILURE));
		if (!(*res = ft_strjoin_free(*res, "\n", 1)))
			return (heredoc_ret(shell, command_line, FAILURE));
	}
	return (KEEP_READ);
}

int			process_heredoc_through_command(char **res, t_shell *shell,
	t_heredoc_func heredoc_func, t_command_line *command_line)
{
	char	*tmp;
	int		ret;

	command_line->to_append = 0;
	if (!(tmp = heredoc_func(command_line->dy_str->str)))
		return (heredoc_ret(shell, command_line, FAILURE));
	if ((command_line->to_append = (refine_heredoc(tmp))) == 0)
	{
		if ((ret = process_heredoc_new_line(res, tmp, shell, command_line))
			!= KEEP_READ)
			return (ret);
	}
	else
	{
		if (append_to_str(&command_line->to_append_str, tmp))
		{
			free(tmp);
			ft_strdel(&command_line->to_append_str);
			return (heredoc_ret(shell, command_line, FAILURE));
		}
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
	ft_strdel(&command_line->to_append_str);
	if (*ret == CTRL_C)
		command_line->interrupted = 1;
	if (*ret == CTRL_D)
		return (heredoc_ret_str(shell, command_line, res));
	else
	{
		free(res);
		return (heredoc_ret_str(shell, command_line, NULL));
	}
}
