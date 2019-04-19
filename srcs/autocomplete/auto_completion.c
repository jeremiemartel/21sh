/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 12:03:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*get_first_word(char *str)
{
	int i;
	int start;

	start = -1;
	i = 0;
	while (str[i])
	{
		if (!ft_isseparator(str[i]) && start == -1)
			start = i;
		else if (ft_isseparator(str[i]) && start != -1)
			return (ft_strndup(&(str[start]), i - start));
		i++;
	}
	if (start == -1)
		return (NULL);
	else
		return (ft_strndup(&(str[start]), i - start));
}

char	*get_completion_str(t_shell *shell)
{
	t_file *file;

	file = (t_file *)shell->autocompletion.choices->content;
	if (ft_dlstlength(shell->autocompletion.choices) == 1)
	{
		shell->autocompletion.choices_common_len++;
		if (!file->unstatable && S_ISDIR(file->st.st_mode))
			return (ft_strjoin(file->name, "/"));
		else
			return (ft_strjoin(file->name, " "));
	}
	else
		return (ft_strndup(file->name,
					shell->autocompletion.choices_common_len));
}

int		process_substitute_command(t_command_line *command_line, char *str,
			t_word word, t_shell *shell)
{
	if (ft_substitute_dy_str(command_line->dy_str, str, word.start_index, word.len))
		return (1);
	command_line->current_index += (shell->autocompletion.choices_common_len - word.index_byte_offset);
	command_line->nb_chars += (ft_strlen_utf8(str) - word.utf8_len);
	render_command_line(command_line->dy_str, shell->autocompletion.choices_common_len - word.index_char_offset);
	return (0);
}

int		process_completion(t_shell *shell, t_command_line *command_line, t_word word)
{
	char *str;

	if (!(str = get_completion_str(shell)))
		return (1);
	if (!ft_strcmp(word.str, str))
	{
		if (ft_dlstlength(shell->autocompletion.choices) == 1)
		{
			if (process_substitute_command(command_line, str, word, shell))
				return (ft_free_turn(str, 1));
		}
		else
		{
		//	ft_printf("show list\n");
		}
	}
	else if (process_substitute_command(command_line, str, word, shell))
		return (ft_free_turn(str, 1));
	return (ft_free_turn(str, 0));
}

int		process_tab(t_shell *shell, t_command_line *command_line)
{
	t_word	word;
	int		ret;

	ret = 0;
	shell->autocompletion.choices_common_len = -1;
	populate_word_by_index(command_line->dy_str->str, command_line->current_index, &word);
	ft_dlstdel(&shell->autocompletion.choices, &free_file_dlst);
	if (populate_choices_from_word(command_line->dy_str, shell, &word))
		return (ft_free_turn(word.str, 1));
	if (shell->autocompletion.choices != NULL)
		ret = process_completion(shell, command_line, word);
	return (ft_free_turn(word.str, ret));
}
