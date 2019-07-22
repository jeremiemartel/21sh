/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 08:53:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/22 10:23:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

void	transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	exit(sh_reset_shell(0));
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

static void transmit_sig_and_exit(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	ft_dprintf(0, "exit\n");
	exit(sh_reset_shell(0));
}

static void transmit_sig_no_motion(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
}

static void	handle_resize(int signal)
{
	(void)signal;
	ioctl(0, TIOCGWINSZ, &g_glob.winsize);
	if (isatty(0) && g_glob.command_line.dy_str)
		render_command_line(&g_glob.command_line, 0, 1);
}

void    handle_stp(int sgnl)
{
	(void)sgnl;
	sh_reset_shell(0);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\x1a");
}

void    handle_cont(int sgnl)
{
	signal(SIGTSTP, handle_stp);
	sh_set_shell_back(0);
	handle_resize(sgnl);
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
	signal(SIGSEGV, transmit_sig_and_die);
	signal(SIGSYS, transmit_sig_and_die);
	signal(SIGPIPE, transmit_sig_and_die);
	signal(SIGALRM, transmit_sig_and_die);
	signal(SIGTERM, transmit_sig_and_exit);
	init_signal_transmit_sig_and_die();
}
