/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_autocompletion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:59:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/17 20:38:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_AUTOCOMPLETION_H
# define SH_AUTOCOMPLETION_H

# include "libft.h"

# define AC_PADDING		2

# define DIR_COLOR		BOLD RED

typedef struct			s_shell t_shell;
typedef struct			s_command_line t_command_line;
//typedef struct			s_command_line t_command_line;

/*
** str:					word content
** start_index:			index of word in the whole string
** word_index:			index of word in the whole string
** len:					len of the word
** index_byte_offset:	index of cursor in the word
** index_char_offset:	nb of chars before the cursor in the word (utf8)
*/
typedef struct		s_word
{
	char			*str;
	char			*to_compare;
	int				start_index;
	int				word_index;
	int				prev_word_index;
	int				len;
	int				utf8_len;
	int				index_byte_offset;
	int				index_char_offset;
}					t_word;

typedef struct		s_file
{
	char			*fullname;
	char			*name;
	char			unstatable;
	struct stat		st;
	int				x;
	int				y;
}					t_file;

typedef struct		s_auto_complete
{
	t_dlist			*head;
	t_dlist			*choices;
	int				choices_common_len;
	char			active;
	int				nb_cols;
	int				nb_lines;
	int				scrolled_lines;
}					t_auto_complete;

/*
** autocompletion.c
*/
char	*get_first_word(char *str);
int		process_tab(t_shell *shell, t_command_line *command_line);
char	*get_completion_str_file(t_file *file);
/*
** preprocess_choice_add.c
*/
int		ft_preprocess_choice_add(t_command_line *line,
			char *entry, t_dlist ***to_add);

/*
** populate_word_by_index.c
*/
int     populate_word_by_index(char *s, int index, t_word *word);

/*
** populate_choices_from_word.c
*/
int     populate_choices_from_word(t_command_line *command_line,
 		t_shell *shell, t_word *word);

/*
** add_choices_from_dir.c
*/
int		add_choices_from_dir(t_shell *shell, t_word *word, char *dirname,
			char *prefix);

/*
** arrows.c
*/

int		process_autocompletion_down(t_command_line *command_line);
int		process_autocompletion_up(t_command_line *command_line);
int		process_autocompletion_left(t_command_line *command_line);
int		process_autocompletion_right(t_command_line *command_line);

/*
** render_choices.c
*/
int		render_choices(t_command_line *command_line);

#endif
