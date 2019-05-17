/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:57:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/20 16:52:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	handle_resize(int signal)
{
	(void)signal;
	ioctl(0, TIOCGWINSZ, &g_glob.winsize);
	if (g_glob.command_line.dy_str)
		render_command_line(&g_glob.command_line, 0, 1);
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
