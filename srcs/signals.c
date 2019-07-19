/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 08:53:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/19 09:04:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

static void	transmit_sig(int signal)
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

static void	handle_resize(int signal)
{
	(void)signal;
	ioctl(0, TIOCGWINSZ, &g_glob.winsize);
	if (isatty(0) && g_glob.command_line.dy_str)
		render_command_line(&g_glob.command_line, 0, 1);
}

void		init_signal_transmit_sig_and_die(void)
{
	signal(SIGALRM, transmit_sig);
	signal(SIGTERM, transmit_sig);
	signal(SIGHUP, transmit_sig);
	signal(SIGABRT, transmit_sig);
	signal(SIGILL, transmit_sig);
	signal(SIGTRAP, transmit_sig);
	signal(SIGEMT, transmit_sig);
	signal(SIGFPE, transmit_sig);
	signal(SIGBUS, transmit_sig);
	signal(SIGSEGV, transmit_sig);
	signal(SIGSYS, transmit_sig);
	signal(SIGTTIN, transmit_sig);
	signal(SIGTTOU, transmit_sig);
	signal(SIGXCPU, transmit_sig);
	signal(SIGXFSZ, transmit_sig);
	signal(SIGVTALRM, transmit_sig);
	signal(SIGPROF, transmit_sig);
	signal(SIGUSR1, transmit_sig);
	signal(SIGUSR2, transmit_sig);
}

void		init_signals(void)
{
	signal(SIGWINCH, handle_resize);
	signal(SIGCONT, transmit_sig);
	signal(SIGQUIT, transmit_sig);
	signal(SIGTSTP, transmit_sig);
	signal(SIGSTOP, transmit_sig);
	signal(SIGKILL, transmit_sig);
	signal(SIGINT, transmit_sig);
	init_signal_transmit_sig_and_die();
}
