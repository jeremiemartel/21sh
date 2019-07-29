/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:59:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/26 09:51:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		putchar_int(int i)
{
	ft_putchar_fd(i, 0);
	return (0);
}

int		sh_reset_shell(int ret)
{
	if (tcsetattr(0, TCSADRAIN, &g_glob.term_init) == -1)
		return (ATTR_ERROR);
	return (ret);
}

int		sh_set_shell_back(int ret)
{
	if (tcsetattr(0, TCSAFLUSH, &g_glob.term) == -1)
		return (ATTR_ERROR);
	return (ret);
}

/*
int		sh_set_shell(struct termios term, int ret)
{
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (ATTR_ERROR);
	return (ret);
}
*/

int		clear_all(void)
{
	char *res;

	if (!(res = tgetstr("cl", NULL)))
		return (-1);
	tputs(res, 1, putchar_int);
	return (0);
}
