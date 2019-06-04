/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_choice_add.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:04:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/22 15:54:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		str_cmp_len(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (i);
}

int		process_preprocess_choice_add(t_command_line *command_line,
			char *entry, int *to_ret, t_dlist ***to_add)
{
	t_dlist *ptr;
	int		ret;
	int		first;
	t_file	*file;

	ptr = command_line->autocompletion.choices;
	first = 1;
	while ((ptr != command_line->autocompletion.choices && ptr != NULL)
		|| (first && ptr != NULL))
	{
		file = ptr->content;
		if (!(ret = ft_strcmp(file->fullname, entry)))
			return (ft_free_turn(entry, 1));
		if (ret > 0 && *to_add == NULL)
		{
			if (ptr == command_line->autocompletion.choices)
				*to_ret = 2;
			*to_add = &(ptr->prev);
		}
		command_line->autocompletion.choices_common_len
			= ft_min(command_line->autocompletion.choices_common_len,
				str_cmp_len(entry, file->fullname));
		ptr = ptr->next;
		first = 0;
	}
	return (0);
}

int		ft_preprocess_choice_add(t_command_line *command_line,
			char *entry, t_dlist ***to_add)
{
	int		to_ret;

	to_ret = 0;
	*to_add = NULL;
	if (command_line->autocompletion.choices == NULL)
	{
		*to_add = &command_line->autocompletion.choices;
		command_line->autocompletion.choices_common_len = ft_strlen(entry);
	}
	if (process_preprocess_choice_add(command_line, entry, &to_ret, to_add))
		return (1);
	if (*to_add == NULL && command_line->autocompletion.choices != NULL)
		*to_add = &command_line->autocompletion.choices->prev;
	return (to_ret);
}
