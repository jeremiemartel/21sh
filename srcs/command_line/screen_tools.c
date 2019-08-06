/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:30:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/06 11:30:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_clear(t_command_line *command_line)
{
	char *str;

	str = tgetstr("cl", NULL);
	tputs(str, 1, putchar_int);
	render_command_line(command_line, 0, 0);
	return (0);
}
