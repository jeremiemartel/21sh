/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:39:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 14:42:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	populate_min_max_selection(t_command_line *command_line, int *min, int *max)
{
	if (command_line->pinned_index < command_line->current_index)
	{
		*min = command_line->pinned_index;
		*max = command_line->current_index;
	}
	else
	{
		*max = command_line->pinned_index;
		*min = command_line->current_index;
	}
}

void	render_command_visual(t_command_line *command_line)
{
	int		min;
	int		max;
	char	*str;

	str = tgetstr("mr", NULL);
	populate_min_max_selection(command_line, &min, &max);
	ft_putnstr_fd(command_line->dy_str->str, min, 0);
	tputs(str, 1, putchar_int);
	ft_putnstr_fd(&command_line->dy_str->str[min], max - min, 0);
	str = tgetstr("me", NULL);
	tputs(str, 1, putchar_int);
	ft_dprintf(0, "%s", &command_line->dy_str->str[max]);
}
