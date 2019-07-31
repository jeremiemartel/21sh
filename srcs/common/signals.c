/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 08:53:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 15:17:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

pid_t g_parent = 0;

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

void		default_sig_bonus(int sgnl)
{
	if (g_parent)
	{
		kill(g_parent, sgnl);
		waitpid(g_parent, NULL, 0);
	}
	signal(sgnl, SIG_DFL);
	sh_reset_shell(0);
	kill(getpid(), sgnl);
}

void		default_sig(int sgnl)
{
  	if (g_parent)
	{
		kill(g_parent, sgnl);
		waitpid(g_parent, NULL, 0);
	}
	sh_reset_shell(0);
	exit(0);
}

void		handle_resize(int signal)
{
	(void)signal;
	if (ioctl(0, TIOCGWINSZ, &g_glob.winsize) == -1)
		exit(sh_reset_shell(1));
	if (isatty(0) && g_glob.command_line.dy_str)
		render_command_line(&g_glob.command_line, 0, 1);
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

void		init_signal_transmit_sig_and_die(void (*default_func)(int))
{
	signal(SIGURG, transmit_sig_no_motion);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, handle_stp);
	signal(SIGCONT, handle_cont);
	signal(SIGCHLD, transmit_sig_no_motion);
	signal(SIGTTIN, transmit_sig_no_motion);
	signal(SIGTTOU, transmit_sig_no_motion);
	signal(SIGIO, transmit_sig_no_motion);
	signal(SIGXCPU, default_func);
	signal(SIGXFSZ, default_func);
	signal(SIGVTALRM, default_func);
	signal(SIGPROF, default_func);
	signal(SIGINFO, transmit_sig_no_motion);
	signal(SIGUSR1, default_func);
	signal(SIGUSR2, default_func);
}

void		init_signals(void)
{
	void (*default_func)(int);

	if (BONUS_REDIRECT_SIGNAL)
		default_func = default_sig_bonus;
	else
		default_func = default_sig;
	signal(SIGWINCH, handle_resize);
	signal(SIGQUIT, transmit_sig_no_motion);
	signal(SIGKILL, default_func);
	signal(SIGINT, transmit_sig);
	signal(SIGHUP, default_func);
	signal(SIGABRT, default_func);
	signal(SIGILL, default_func);
	signal(SIGTRAP, default_func);
	signal(SIGEMT, default_func);
	signal(SIGFPE, default_func);
	signal(SIGBUS, default_func);
	signal(SIGSEGV, default_func);
	signal(SIGSYS, default_func);
	signal(SIGPIPE, transmit_sig_and_die);
	signal(SIGALRM, default_func);
	signal(SIGTERM, transmit_sig_and_exit);
	init_signal_transmit_sig_and_die(default_func);
}
