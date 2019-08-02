/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here_canonical.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:29:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 18:47:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			populate_command_line(t_command_line *command_line, char *str)
{
	ft_strdel(&command_line->dy_str->str);
	command_line->dy_str->str = str;
}

static int		process_heredoc_canonical_mode(t_gnl_info info,
					char **res, t_shell *shell,
						char *(*heredoc_func)(const char *))
{
	int			ret;

	if (info.separator != E_SEPARATOR_ZERO)
	{
		populate_command_line(&g_glob.command_line, info.line);
		if ((ret = process_heredoc_through_command(res, shell, heredoc_func,
			&g_glob.command_line)) != 3)
			return (ret);
	}
	else
	{
		free(info.line);
		return (sh_perror("Illegal characters received from input",
					"heredoc_canonical_mode"));
	}
	return (3);
}

int				heredoc_canonical_mode_eof(char *eof, char **res)
{
	if (g_glob.command_line.to_append_str)
	{
		if (ft_strcmp(g_glob.command_line.to_append_str, eof))
		{
			ft_dprintf(2, "21sh: warning: here-document "
					"delimited by end of file (wanted `%s')\n", eof);
			if (!(*res = ft_strjoin_free(*res,
				g_glob.command_line.to_append_str, 1)))
			{
				ft_strdel(&g_glob.command_line.to_append_str);
				return (1);
			}
			if (!(*res = ft_strjoin_free(*res, "\n", 1)))
			{
				ft_strdel(&g_glob.command_line.to_append_str);
				return (1);
			}
		}
	}
	return (0);
}

char			*heredoc_gnl_error(int *ret, char **res)
{
	*ret = -2;
	ft_strdel(&g_glob.command_line.to_append_str);
	return (ft_free_turn_str(res, NULL));
}

char			*heredoc_canonical_mode(t_shell *shell, char *eof,
					char *(*heredoc_func)(const char *), int *ret)
{
	int			gnl_ret;
	t_gnl_info	info;
	char		*res;

	if (!(res = ft_strnew(0)))
		return (sh_perrorn(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
	g_glob.command_line.heredoc_eof = eof;
	while ((gnl_ret = get_next_line2(0, &info, 1)) == 1)
	{
		if ((*ret = process_heredoc_canonical_mode(info,
				&res, shell, heredoc_func)) != 3)
		{
			if (*ret == SUCCESS)
				return (res);
			else
				return (NULL);
		}
	}
	if (gnl_ret == -1)
		return (heredoc_gnl_error(ret, &res));
	free(info.line);
	*ret = SUCCESS;
	if (heredoc_canonical_mode_eof(eof, &res))
		return (NULL);
	return (res);
}
