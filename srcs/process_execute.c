/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/27 00:39:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t g_parent = 0;

void	transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	return (exit(reset_shell(0)));
}

void	transmit_sig(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	get_down_from_command(g_glob.command);
	g_glob.cursor = 0;
	g_glob.command->current_size = 0;
	g_glob.command->current_index = 0;
	ft_bzero(g_glob.command->str, g_glob.command->max_size);
	g_glob.command->nb_chars = 0;
	render_command_line(g_glob.command, 0);
}

int		process_execute(char *path, t_shell *shell)
{
	if (check_execute(path, shell))
		return (1);
	if (reset_shell(0) == -1)
		return (1);
	if ((g_parent = fork()) == -1)
		return (1);
	if (g_parent == 0)
	{
		if (execve(path, shell->params, (char **)shell->env->tbl) == -1)
		{
			free_all(shell);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		g_parent = 0;
		if (set_shell(0) == -1)
			return (1);
	}
	return (0);
}
