/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:14:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/11 19:43:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*heredoc(t_command_line *command_line, char *stop)
{
	char *res;

	(void)stop;
	(void)res;
	render_command_line(command_line, -g_glob.cursor);
	return (NULL);
}
