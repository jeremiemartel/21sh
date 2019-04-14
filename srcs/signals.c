/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:57:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 16:34:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	transmit_sig_and_die(int signal)
{
	(void)signal;
	//  if (g_parent)
	//      kill(g_parent, signal);
	return (exit(sh_reset_shell(0)));
}

void	transmit_sig(int signal)
{
	(void)signal;
	//  if (g_parent)
	//      kill(g_parent, signal);
	get_down_from_command(&g_glob.command_line);
	g_glob.cursor = 0;
	g_glob.command_line.dy_str->current_size = 0;
	g_glob.command_line.current_index = 0;
	ft_bzero(g_glob.command_line.dy_str->str, g_glob.command_line.dy_str->max_size);
	g_glob.command_line.nb_chars = 0;
	render_command_line(g_glob.command_line.dy_str, 0);
}

void	handle_resize(int signal)
{
	(void)signal;
	ioctl(0, TIOCGWINSZ, &g_glob.winsize);
	if (g_glob.command_line.dy_str)
		render_command_line(g_glob.command_line.dy_str, 0);
}

void	init_signals(void)
{
	signal(SIGWINCH, handle_resize);
	signal(SIGALRM, transmit_sig_and_die);
	signal(SIGTERM, transmit_sig_and_die);
	signal(SIGHUP, transmit_sig_and_die);
	signal(SIGABRT, transmit_sig_and_die);
	signal(SIGCONT, transmit_sig);
	signal(SIGQUIT, transmit_sig);
	signal(SIGTSTP, transmit_sig);
	signal(SIGSTOP, transmit_sig);
	signal(SIGKILL, transmit_sig);
	signal(SIGINT, transmit_sig);
}
