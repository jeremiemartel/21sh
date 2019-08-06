/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:06:46 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 00:09:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char		*get_completion_str_file(t_file *file)
{
	if (!file->unstatable && S_ISDIR(file->st.st_mode))
		return (ft_strjoin(file->fullname, "/"));
	else
		return (ft_strjoin(file->fullname, " "));
}

char		*get_completion_str(t_command_line *command_line)
{
	t_file *file;

	file = (t_file *)command_line->autocompletion.choices->content;
	if (ft_dlstlength(command_line->autocompletion.choices) == 1)
		return (get_completion_str_file(file));
	else
		return (ft_strndup(file->fullname,
			command_line->autocompletion.choices_common_len));
}
