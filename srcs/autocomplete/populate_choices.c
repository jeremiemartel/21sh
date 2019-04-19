/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_choices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 12:03:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		add_choices_path(t_shell *shell, t_word *word, char *path_str)
{
	char	**path_split;
	int		i;

	if (!(path_split = ft_strsplit(path_str, ':')))
		return (1);
	i = 0;
	while (path_split[i])
	{
		if (add_choices_from_dir(shell, word, path_split[i], NULL))
		{
			ft_strtab_free(path_split);
			return (1);
		}
		i++;
	}
	ft_strtab_free(path_split);
	return (0);
}

int		populate_choices_from_binaries(t_shell *shell, t_word *word)
{
	char *path_str;

	word->to_compare = word->str;
	if ((path_str = get_env_value((char **)shell->env->tbl, "PATH")))
	{
		if (add_choices_path(shell, word, path_str))
			return (1);
		return (0);
	}
	else
		return (0);
}

int		populate_choices_from_folder(t_shell *shell, t_word *word)
{
	char	*path;
	char	*transformed_path;
	char	*file;

	if (get_path_and_file_from_str(word->str,
			&transformed_path, &file))
		return (1);
	if (!(path = ft_strdup(transformed_path)))
	{
		free(file);
		return (ft_free_turn(transformed_path, 1));
	}
//	if (!ft_strncmp(path, "~/", 2) &&
//			process_subst_home(shell, &transformed_path))
//		return (ft_free_turn_3(file, transformed_path, path, 1));
	word->to_compare = file;
	if (add_choices_from_dir(shell, word, transformed_path, path))
		return (1);
	return (ft_free_turn_3(file, transformed_path, path, 0));
}

int		populate_choices_from_folder_binary(t_shell *shell, char *binary,
			t_word *word)
{
	free(binary);
	return (populate_choices_from_folder(shell, word));
}

int		populate_choices_from_word(t_dy_str *command,
		t_shell *shell, t_word *word)
{
	char *binary;

	if (word->word_index == 1 || (word->word_index == 0))
	{
		if (populate_choices_from_binaries(shell, word))
			return (1);
		if (shell->autocompletion.choices == NULL)
		{
			if (populate_choices_from_folder(shell, word))
				return (1);
		}
	}
	else
	{
		if (!(binary = get_first_word(command->str)))
			return (1);
		if (populate_choices_from_folder_binary(shell, binary, word))
			return (1);
	}
	return (0);
}
