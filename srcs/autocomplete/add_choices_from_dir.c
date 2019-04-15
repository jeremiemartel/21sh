/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_from_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 12:03:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		add_node_next_to_node(t_dlist **node, t_dlist *to_add)
{
	t_dlist *tmp;

	if (*node)
	{
		tmp = (*node)->next;
		(*node)->next = to_add;
		(to_add)->prev = (*node);
		(to_add)->next = tmp;
		(to_add)->next->prev = to_add;
	}
	else
		*node = to_add;
}

t_file		*new_file(t_shell *shell, char *str)
{
	t_file	*res;
	char	*path;

	if (!(res = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	res->name = str;
	if (!(path = ft_strdup(res->name)))
	{
		free(res);
		return (NULL);
	}
//	if (!ft_strncmp(path, "~/", 2) &&
//			process_subst_home(shell, &path))
//	{
//		free(path);
//		free(res);
//		return (NULL);
//	}
	if (lstat(path, &res->st) == -1)
		res->unstatable = 1;
	else
		res->unstatable = 0;
	free(path);
	return (res);
}

int			process_add_choices_from_dir(t_shell *shell,
			struct dirent *entry, char *prefix)
{
	char			*str;
	t_dlist			**prev_to_add;
	t_dlist			*to_add;
	int				ret;
	t_file			*file;

	if (!prefix && !(str = ft_strdup(entry->d_name)))
		return (1);
	else if (prefix && !(str = ft_strjoin(prefix, entry->d_name)))
		return (1);
	if ((ret = ft_preprocess_choice_add(shell, str, &prev_to_add)) != 1)
	{
		if (!(file = new_file(shell, str)))
			return (ft_free_turn(str, 1));
		if (!(to_add = ft_dlstnew_ptr(file, sizeof(t_file))))
			return (ft_free_turn_2(str, file, 1));
		add_node_next_to_node(prev_to_add, to_add);
		if (ret)
			shell->autocompletion.choices = shell->autocompletion.choices->prev;
	}
	return (0);
}

int			add_choices_from_dir(t_shell *shell, t_word *word, char *dirname,
			char *prefix)
{
	DIR				*dir;
	struct dirent	*entry;
	int				len;

	len = ft_strlen(word->to_compare);
	if (!ft_strcmp(dirname, "") && !(dir = opendir(".")))
		return (0);
	else if (ft_strcmp(dirname, "") && !(dir = opendir(dirname)))
		return (0);
	while ((entry = readdir(dir)) != NULL)
	{
		if (!ft_strncmp(entry->d_name, ".", 1) && word->to_compare[0] != '.')
			continue;
		if (!ft_strncmp(entry->d_name, word->to_compare, len))
		{
			if (process_add_choices_from_dir(shell, entry, prefix))
			{
				closedir(dir);
				return (1);
			}
		}
	}
	closedir(dir);
	return (0);
}
