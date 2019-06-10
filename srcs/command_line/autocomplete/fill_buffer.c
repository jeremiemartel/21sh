/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 02:19:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/04 02:19:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	fill_buffer_padding(char **print_buffer)
{
	int i;

	i = 0;
	while (i < AC_PADDING)
	{
		ft_strcpy(*print_buffer, " ");
		(*print_buffer)++;
		i++;
	}
}

void	process_fill_buffer_folder_suffix(int is_current,
	char **print_buffer, int *i)
{
	if (!is_current)
	{
		ft_strcpy(*print_buffer, EOC);
		*print_buffer += ft_strlen(EOC);
	}
	ft_strcpy(*print_buffer, BOLD"/");
	*print_buffer += ft_strlen(BOLD"/");
	if (!is_current)
	{
		ft_strcpy(*print_buffer, EOC);
		*print_buffer += ft_strlen(EOC);
	}
	*i += 1;
}

void	process_fill_buffer_from_file(t_file *file, int is_current,
			char **print_buffer, int *i)
{
	char	*str;

	str = tgetstr("mr", NULL);
	if (is_current)
	{
		ft_strcpy(*print_buffer, str);
		*print_buffer += ft_strlen(str);
	}
	else if (!file->unstatable && S_ISDIR(file->st.st_mode))
	{
		ft_strcpy(*print_buffer, DIR_COLOR);
		*print_buffer += ft_strlen(DIR_COLOR);
	}
	ft_strcpy(*print_buffer, file->name);
	*i = ft_strlen(file->name);
	*print_buffer += *i;
	if (!file->unstatable && S_ISDIR(file->st.st_mode))
		process_fill_buffer_folder_suffix(is_current, print_buffer, i);
}

void	fill_buffer_from_file(t_command_line *command_line,
			char **print_buffer, t_file *file, int max_len)
{
	int		i;
	int		is_current;

	i = 0;
	is_current = command_line->autocompletion.head
		&& file == command_line->autocompletion.head->content;
	if (file)
		process_fill_buffer_from_file(file, is_current, print_buffer, &i);
	while (command_line->autocompletion.nb_cols > 1 && i < max_len)
	{
		ft_strcpy(*print_buffer, " ");
		(*print_buffer)++;
		i++;
	}
	if (is_current)
	{
		ft_strcpy(*print_buffer, EOC);
		*print_buffer += ft_strlen(EOC);
	}
}
