/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:57:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 15:45:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

static void	transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	return (exit(sh_reset_shell(0)));
}

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

void	init_signal_transmit_sig_and_die(void)
{
	signal(SIGALRM, transmit_sig_and_die);
	signal(SIGTERM, transmit_sig_and_die);
	signal(SIGHUP, transmit_sig_and_die);
	signal(SIGABRT, transmit_sig_and_die);
	signal(SIGILL, transmit_sig_and_die);
	signal(SIGTRAP, transmit_sig_and_die);
	signal(SIGEMT, transmit_sig_and_die);
	signal(SIGFPE, transmit_sig_and_die);
	signal(SIGBUS, transmit_sig_and_die);
	signal(SIGSEGV, transmit_sig_and_die);
	signal(SIGSYS, transmit_sig_and_die);
	signal(SIGTTIN, transmit_sig_and_die);
	signal(SIGTTOU, transmit_sig_and_die);
	signal(SIGXCPU, transmit_sig_and_die);
	signal(SIGXFSZ, transmit_sig_and_die);
	signal(SIGVTALRM, transmit_sig_and_die);
	signal(SIGPROF, transmit_sig_and_die);
	signal(SIGUSR1, transmit_sig_and_die);
	signal(SIGUSR2, transmit_sig_and_die);
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
