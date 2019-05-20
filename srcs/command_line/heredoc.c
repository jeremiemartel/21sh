/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:14:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/20 18:11:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char *heredoc_ret(t_command_line *command_line, char *str)
{
	command_line->context = E_CONTEXT_STANDARD;
	update_prompt(command_line);
	return (str);
}

char	*heredoc(t_shell *shell, char *stop,
			char *(*heredoc_func)(char *), int *ret)
{
	char	*res;
	t_command_line *command_line;

	command_line = &g_glob.command_line;
	if (!(res = ft_strnew(0)))
		return (heredoc_ret(command_line, NULL));
	flush_command_line(command_line);
	render_command_line(command_line, - g_glob.cursor, 1);
	command_line->context = E_CONTEXT_HEREDOC;
	update_prompt(command_line);
	while ((*ret = sh_get_command(shell, command_line)) == SUCCESS)
	{
		if (!(res = heredoc_func(res)))
			return (heredoc_ret(command_line, NULL));
		if (!ft_strcmp(command_line->dy_str->str, stop))
			return (heredoc_ret(command_line, res));
		else
		{
			if (!(res = ft_strjoin_free(res, command_line->dy_str->str, 1)))
				return (heredoc_ret(command_line, NULL));
			if (!(res = ft_strjoin_free(res, "\n", 1)))
				return (heredoc_ret(command_line, NULL));
		}
	}
	if (*ret == CTRL_D)
		return (heredoc_ret(command_line, res));
	else
		return (heredoc_ret(command_line, NULL));
}
