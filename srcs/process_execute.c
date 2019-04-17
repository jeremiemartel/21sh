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

#include "sh_21.h"

static pid_t g_parent = 0;

void	transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	return (exit(sh_reset_shell(0)));
}

void	transmit_sig(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	get_down_from_command(&g_glob.command_line);
	g_glob.cursor = 0;
	g_glob.command_line.dy_str->current_size = 0;
	g_glob.command_line.current_index = 0;
	ft_bzero(g_glob.command_line.dy_str->str, g_glob.command_line.dy_str->max_size);
	g_glob.command_line.nb_chars = 0;
	render_command_line(g_glob.command_line.dy_str, 0);
}

int		process_execute(char *path, t_context *context)
{
	if (check_execute(path, context->params->tbl[0]))
		return (1);
	if (isatty(0) && sh_reset_shell(0) == -1)
		return (1);
	if ((g_parent = fork()) == -1)
		return (1);
	if (g_parent == 0)
	{
		if (execve(path, (char **)context->params->tbl,
				(char **)context->env->tbl) == -1)
		{
	//		free_all(shell);
	//		exit(1);
		}
	}
	else
	{
		wait(NULL);
		g_parent = 0;
		if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (ft_perror("Could not modify this terminal attributes",
				"process_execute"));
	}
	return (0);
}
