/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_line_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 09:50:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 15:45:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_eof_delimiter(void)
{
	char *res;

	res = tgetstr("ce", NULL);
	tputs(res, 1, putchar_int);
	res = tgetstr("mr", NULL);
	tputs(res, 1, putchar_int);
	ft_printf("%%");
	res = tgetstr("me", NULL);
	tputs(res, 1, putchar_int);
}

int		sh_add_eof(int interrupted)
{
	int x;

	if (!interrupted && 1)
	{
		if (sh_get_cursor_position(&x, NULL) != SUCCESS)
			return (FAILURE);
		else if (x != 1)
		{
			print_eof_delimiter();
			ft_dprintf(1, "\n");
		}
	}
	return (SUCCESS);
}
