/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:14:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/11 19:43:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char *heredoc_ret(t_command_line *command_line, char *back, char *str)
{
	switch_prompt(command_line, back);
	return (str);
}

char	*heredoc(t_shell *shell, t_command_line *command_line, char *stop)
{
	char	*res;
	char	*new;
	int		ret;
	char	*back;

	if (!(back = ft_strdup(command_line->prompt)))
		return (NULL);
	if (!(new = ft_strdup(HEREDOC_PROMPT)))
		return (heredoc_ret(command_line, back, NULL));
	if (!(res = ft_strnew(0)))
		return (heredoc_ret(command_line, back, NULL));
	flush_command_line(command_line);
	render_command_line(command_line, - g_glob.cursor);
	switch_prompt(command_line, new);
	while ((ret = sh_get_command(shell, command_line) == SUCCESS))
	{
		if (!ft_strcmp(command_line->dy_str->str, stop))
			return (heredoc_ret(command_line, back, res));
		else if (!(res = ft_strjoin_free(res, command_line->dy_str->str, 1)))
			return (heredoc_ret(command_line, back, NULL));
	}
	if (ret == CTRL_D)
		return (heredoc_ret(command_line, back, res));
	else
		return (heredoc_ret(command_line, back, NULL));
}
