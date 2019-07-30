/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 10:38:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/30 10:14:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

void	transmit_sig(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	if (isatty(0) && g_glob.command_line.dy_str)
	{
		get_down_from_command(&g_glob.command_line);
		g_glob.cursor = 0;
		g_glob.command_line.dy_str->current_size = 0;
		g_glob.command_line.current_index = 0;
		ft_bzero(g_glob.command_line.dy_str->str,
				g_glob.command_line.dy_str->max_size);
		g_glob.command_line.nb_chars = 0;
		render_command_line(&g_glob.command_line, 0, 1);
	}
}

void	transmit_sig_and_exit(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	ft_dprintf(0, "exit\n");
	exit(sh_reset_shell(0));
}

void	handle_stp(int sgnl)
{
	(void)sgnl;
	sh_reset_shell(0);
	ft_printf("2 DOUA\n");
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\x1a");
}

void	handle_cont(int sgnl)
{
	signal(SIGTSTP, handle_stp);
	sh_set_shell_back(0);
	handle_resize(sgnl);
}
