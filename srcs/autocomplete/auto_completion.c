/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/06 18:41:40 by ldedier          ###   ########.fr       */
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

char	*get_completion_str_file(t_file *file)
{
	if (!file->unstatable && S_ISDIR(file->st.st_mode))
		return (ft_strjoin(file->fullname, "/"));
	else
		return (ft_strjoin(file->fullname, " "));
}

char	*get_completion_str(t_command_line *command_line)
{
	t_file *file;

	file = (t_file *)command_line->autocompletion.choices->content;
	if (ft_dlstlength(command_line->autocompletion.choices) == 1)
		return (get_completion_str_file(file));
	else
		return (ft_strndup(file->fullname,
			command_line->autocompletion.choices_common_len));
}

int		process_substitute_command(t_command_line *command_line, char *str,
			t_word word)
{
	int len;
	int utf8_len;

	len = ft_strlen(str);
	utf8_len = ft_strlen_utf8(str);

	if (ft_substitute_dy_str(command_line->dy_str, str, word.start_index, word.len))
		return (1);
	command_line->current_index += (len - word.index_byte_offset);
	command_line->nb_chars += (utf8_len - word.utf8_len);
	render_command_line(command_line, utf8_len - word.index_char_offset);
	return (0);
}

int		process_advanced_completion(t_command_line *command_line, t_word word)
{
	t_file *file;

	if (command_line->autocompletion.head)
		command_line->autocompletion.head = command_line->autocompletion.head->next;
	else
		command_line->autocompletion.head = command_line->autocompletion.choices;
	file = (t_file *)command_line->autocompletion.head->content;
	if (process_substitute_command(command_line, file->fullname, word))
		return (FAILURE);
	render_command_line(command_line, 0);
	return (SUCCESS);
}

int		process_completion(t_command_line *command_line, t_word word)
{
	char	*str;

	if (!(str = get_completion_str(command_line)))
		return (1);
	if (!ft_strcmp("", word.str) || (!ft_strcmp(word.str, str) && word.start_index + word.len == command_line->current_index))
	{
		if (ft_dlstlength(command_line->autocompletion.choices) == 1)
		{
	//		command_line->autocompletion.active = 0;
			if (process_substitute_command(command_line, str, word))
				return (ft_free_turn(str, 1));
		}
		else
		{
			command_line->autocompletion.active = 1;
		//	command_line->autocompletion.head = command_line->autocompletion.choices;
			if (word.word_index == 0)
			{
				if (process_substitute_command(command_line, str, word))
					return (FAILURE);
			}
			render_command_line(command_line, 0);
		}
	}
	else
	{
		if (process_substitute_command(command_line, str, word))
			return (ft_free_turn(str, 1));
	}
	return (ft_free_turn(str, 0));
}

void print_word(t_word word)
{
	ft_printf("\n\nword_index: %d\n", word.word_index);
	ft_printf("word_prev_index: %d\n", word.prev_word_index);
	ft_printf("word_start_index: %d\n", word.start_index);
	ft_printf("str: %s\n", word.str);
}

int		process_tab(t_shell *shell, t_command_line *command_line)
{
	t_word	word;
	int		ret;

	ret = 0;
	command_line->autocompletion.choices_common_len = -1;
	populate_word_by_index(command_line->dy_str->str, command_line->current_index, &word);
//	print_word(word);
//	exit(sh_reset_shell(0));
	if (!command_line->autocompletion.active)
	{
	//	ft_printf(RED"ON FREE\n");
		ft_dlstdel(&command_line->autocompletion.choices, &free_file_dlst);
		if (populate_choices_from_word(command_line, shell, &word))
			return (ft_free_turn(word.str, 1));
		if (command_line->autocompletion.choices != NULL)
			ret = process_completion(command_line, word);
	}
	else
		process_advanced_completion(command_line, word);
	return (ft_free_turn(word.str, ret));
}
