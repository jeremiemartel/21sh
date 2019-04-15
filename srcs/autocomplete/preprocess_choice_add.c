/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_choice_add.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:04:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 12:04:17 by ldedier          ###   ########.fr       */
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

int		process_preprocess_choice_add(t_shell *shell,
			char *entry, int *to_ret, t_dlist ***to_add)
{
	t_dlist *ptr;
	int		ret;
	int		first;
	t_file	*file;

	ptr = shell->autocompletion.choices;
	first = 1;
	while ((ptr != shell->autocompletion.choices && ptr != NULL) || (first && ptr != NULL))
	{
		file = ptr->content;
		if (!(ret = ft_strcmp(file->name, entry)))
			return (ft_free_turn(entry, 1));
		if (ret > 0 && *to_add == NULL)
		{
			if (ptr == shell->autocompletion.choices)
				*to_ret = 2;
			*to_add = &(ptr->prev);
		}
		shell->autocompletion.choices_common_len = ft_min(shell->autocompletion.choices_common_len,
				str_cmp_len(entry, file->name));
		ptr = ptr->next;
		first = 0;
	}
	return (0);
}

int		ft_preprocess_choice_add(t_shell *shell, char *entry, t_dlist ***to_add)
{
	int		to_ret;

	to_ret = 0;
	*to_add = NULL;
	if (shell->autocompletion.choices == NULL)
	{
		*to_add = &shell->autocompletion.choices;
		shell->autocompletion.choices_common_len = ft_strlen(entry);
	}
	if (process_preprocess_choice_add(shell, entry, &to_ret, to_add))
		return (1);
	if (*to_add == NULL && shell->autocompletion.choices != NULL)
		*to_add = &shell->autocompletion.choices->prev;
	return (to_ret);
}
