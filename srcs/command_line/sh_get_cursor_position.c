/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_cursor_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 07:35:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/19 09:02:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		get_cursor_position_from_answer(int *x, int *y, char *answer,
		int answer_len)
{
	char	*str;
	int		tmp_y;

	str = answer + ft_min(2, answer_len - 1);
	tmp_y = ft_patoi(&str);
	if (y)
		*y = tmp_y;
	str += ft_min(1, answer_len - (str - answer));
	if (x)
		*x = ft_atoi(str);
}

int				sh_get_cursor_position(int *x, int *y)
{
	int				fd;
	char			answer[4096];
	size_t			answer_len;

	fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
	{
		return (sh_perror("Could not get cursor position",
			"sh_get_cursor_position"));
	}
	write(fd, "\x1B[6n", 5);
	answer_len = 0;
	while (answer_len < sizeof(answer) - 1
			&& read(fd, answer + answer_len, 1) == 1)
	{
		if (answer[answer_len++] == 'R')
			break ;
		else if (answer_len == 4096)
		{
			close(fd);
			return (sh_perror("Could not get cursor position",
				"sh_get_cursor_position"));
		}
	}
	close(fd);
	answer[answer_len] = '\0';
	get_cursor_position_from_answer(x, y, answer, answer_len);
	return (SUCCESS);
}
