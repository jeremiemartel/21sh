/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 16:07:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			reset_signals(void)
{
	int i;

	i = 1;
	while (i <= SIGUSR2)
		signal(i++, SIG_DFL);
}

static void		init_signal2(void (*default_func)(int))
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

void			init_signals(void)
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
	init_signal2(default_func);
}
