/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 08:53:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 18:03:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

static void	transmit_sig_no_motion(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
}

void		transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	exit(sh_reset_shell(0));
}

void		handle_resize(int signal)
{
	(void)signal;
	ioctl(0, TIOCGWINSZ, &g_glob.winsize);
	if (isatty(0) && g_glob.command_line.dy_str)
		render_command_line(&g_glob.command_line, 0, 1);
}

void		init_signal_transmit_sig_and_die(void)
{
	signal(SIGURG, transmit_sig_no_motion);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, handle_stp);
	signal(SIGCONT, handle_cont);
	signal(SIGCHLD, transmit_sig_no_motion);
	signal(SIGTTIN, transmit_sig_no_motion);
	signal(SIGTTOU, transmit_sig_no_motion);
	signal(SIGIO, transmit_sig_no_motion);
	signal(SIGXCPU, transmit_sig_and_die);
	signal(SIGXFSZ, transmit_sig_and_die);
	signal(SIGVTALRM, transmit_sig_and_die);
	signal(SIGPROF, transmit_sig_and_die);
	signal(SIGINFO, transmit_sig_no_motion);
	signal(SIGUSR1, transmit_sig_and_die);
	signal(SIGUSR2, transmit_sig_and_die);
}

void		reset_signals()
{
	signal(SIGURG, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGIO, SIG_DFL);
	signal(SIGXCPU, SIG_DFL);
	signal(SIGXFSZ, SIG_DFL);
	signal(SIGVTALRM, SIG_DFL);
	signal(SIGPROF, SIG_DFL);
	signal(SIGINFO, SIG_DFL);
	signal(SIGUSR1, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGKILL, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGTRAP, SIG_DFL);
	signal(SIGEMT, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGSYS, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGALRM, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGUSR2, SIG_DFL);
}

void		init_signals(void)
{
	signal(SIGWINCH, handle_resize);
	signal(SIGQUIT, transmit_sig_no_motion);
	signal(SIGKILL, transmit_sig);
	signal(SIGINT, transmit_sig);
	signal(SIGHUP, transmit_sig_and_die);
	signal(SIGABRT, transmit_sig_and_die);
	signal(SIGILL, transmit_sig_and_die);
	signal(SIGTRAP, transmit_sig_and_die);
	signal(SIGEMT, transmit_sig_and_die);
	signal(SIGFPE, transmit_sig_and_die);
	signal(SIGBUS, transmit_sig_and_die);
	signal(SIGSEGV, SIG_DFL);// transmit_sig_and_die);
	signal(SIGSYS, transmit_sig_and_die);
	signal(SIGPIPE, transmit_sig_and_die);
	signal(SIGALRM, transmit_sig_and_die);
	signal(SIGTERM, transmit_sig_and_exit);
	init_signal_transmit_sig_and_die();
}
