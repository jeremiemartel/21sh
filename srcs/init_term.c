/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:41:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_terminal_database(char **env)
{
	char	*termtype;
	int		success;

	termtype = get_env_value(env, "TERM");
	if (termtype == NULL)
	{
		return (sh_perror("Specify a terminal type with 'export TERM'",
				"sh_init_terminal_database"));
	}
	success = tgetent(NULL, termtype);
	if (success < 0)
	{
		return (sh_perror("Could not access the termcap data base",
				"sh_init_terminal_database"));
	}
	if (success == 0)
	{
		return (sh_perror("The terminal specified is not defined",
					"sh_init_terminal_database"));
	}
	return (SUCCESS);
}

int		sh_init_terminal(t_shell *shell, char **env)
{
	if (sh_init_terminal_database(env))
		return (1);
	if (tcgetattr(0, &shell->term) == -1)
		return (sh_perror(SH_ERR1_TERM_CPY, "sh_init_terminal"));
	if (tcgetattr(0, &g_glob.term_init) == -1)
		return (sh_perror(SH_ERR1_TERM_CPY, "sh_init_terminal"));
	shell->term.c_lflag &= ~(ICANON);
	shell->term.c_lflag &= ~(ECHO);
	shell->term.c_lflag |= ISIG;
	shell->term.c_lflag &= ~(ISIG);
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &shell->term) == -1)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	}
	ioctl(0, TIOCGWINSZ, &g_glob.winsize);
	return (0);
}
