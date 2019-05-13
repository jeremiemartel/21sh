/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:20:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/13 18:30:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_COMMAND_LINE_H
# define SH_COMMAND_LINE_H

# include "libft.h"

# define PROMPT			"$21_sh(to_rework)> "
# define COMMAND_PROMPT	"$21_sh(to_rework(command))> "
# define VISUAL_PROMPT	"$21_sh(to_rework(visual))> "
# define HISTORIC_FILE	".historic"
# define HEREDOC_PROMPT	"heredoc> "
# define READ_BUFF_SIZE	4

typedef enum		e_mode
{
	E_MODE_INSERT,
	E_MODE_VISUAL,
	E_MODE_COMMAND
}					t_mode;

typedef enum		e_command_line_context
{
	E_CONTEXT_STANDARD,
	E_CONTEXT_HEREDOC,
}					t_command_line_context;

typedef struct				s_command_line
{
	char					*prompt;
	t_dy_str				*dy_str;
	int						nb_chars;
	int						current_index;
	t_auto_complete 		autocompletion;
	t_mode					mode;
	char					*clipboard;
	int						pinned_index;
	int						last_char_input;
	t_command_line_context	context;
}							t_command_line;

typedef struct		s_historic
{
	t_dlist			*head;
	t_dlist			*commands;
	t_dlist			head_start;
}					t_historic;

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct      s_glob
{
	struct termios	term_init;
	t_command_line	command_line;
	int				cursor;
	struct winsize	winsize;
}					t_glob;

t_glob				g_glob;

/*
** shell_tools.c
*/

int			sh_reset_shell(int ret);
int			putchar_int(int i);
void		move(int x, int y);
int			clear_all(void);

/*
** get_command.c
*/
void		reset_command_line(t_shell *shell, t_command_line *command_line);
int			render_command_line(t_command_line *command_line, int cursor_inc);
int			sh_get_command(t_shell *shell, t_command_line *command_line);

/*
** edit_command.c
*/
void    process_edit_command_left(t_command_line *command_line);
void    process_edit_command_right(t_command_line *command_line);
void	process_suppr(t_command_line *command_line);
void	process_delete(t_command_line *command_line);

/*
** cursor_motion.c
*/
int		get_true_cursor_pos(int cursor);
int		get_down_from_command(t_command_line *command_line);
int		process_clear(t_command_line *command_line);
int		go_up_to_prompt(int width, int cursor);
void	go_up_left(int up);
void	go_right(int right);
void	replace_cursor_after_render(void);
void	replace_cursor_on_index(void);


/*
** utf8_tools.c
*/

int     ft_strlen_utf8(char *str);
int     ft_strnlen_utf8(char *str, int n);
int		get_left_w_char_index(t_command_line *command_line);
int		get_right_w_char_index(t_command_line *command_line);

/*
** is_printable_utf8.c
*/
int		is_printable_utf8(unsigned char *buffer, int nb_bytes);

/*
** keys.c
*/
int		 get_keys(t_shell *shell, t_command_line *command_line);

/*
** keys_insert.c
*/
int		process_keys_insert(unsigned char buffer[READ_BUFF_SIZE],
			t_shell *shell, t_command_line *command_line, int ret);
/*
** keys_others.c
*/
int		process_keys_others(unsigned char buffer[READ_BUFF_SIZE],
			t_command_line *command_line);

/*
** process_historic.c
*/
int		process_historic_up(t_shell *shell, t_command_line *command_line);
int		process_historic_down(t_shell *shell, t_command_line *command_line);
/*
** tools.c
*/
void	ring_bell(void);
void	flush_command_line(t_command_line *command_line);
int		get_file_in_dir(char *filename, char *dirname);
int		get_path_and_file_from_str(char *str, char **path, char **file);

/*
** process_shift.c
*/
int		process_shift_right(t_command_line *command_line);
int		process_shift_left(t_command_line *command_line);
int		process_shift_up(t_command_line *command_line);
int		process_shift_down(t_command_line *command_line);

/*
** arrows.c
*/
int		process_down(t_shell *shell, t_command_line *command_line);
int		process_up(t_shell *shell, t_command_line *command_line);
int		process_left(t_shell *shell, t_command_line *command_line);
int		process_right(t_shell *shell, t_command_line *command_line);

/*
** home_end.c
*/
int		process_start(t_command_line *command_line);
int		process_end(t_command_line *command_line);

/*
** command_line.c
*/
int		substitute_current_index(t_command_line *command_line, t_file *file);
void	flush_command_line(t_command_line *command_line);
int		process_substitute_command(t_command_line *command_line,
			char *str, t_word word);
int		paste_current_index(t_command_line *command_line, char *to_paste);
int		delete_command_line_selection(t_command_line *command_line);
int		command_line_nb_rows(t_command_line *command_line);
/*
** xy.c
*/
t_xy	get_position(int cursor);
int		xy_is_equal(t_xy xy1, t_xy xy2);

/*
** render_choices.c
*/
void	render_choices(t_command_line *command_line);

/*
** switch_prompt.c
*/
int		process_escape(t_command_line *command_line);
int		process_i(t_command_line *command_line);
int		process_v(t_command_line *command_line);
void	switch_prompt(t_command_line *command_line, char *new_prompt);

/*
** copy_paste_delete.c
*/

int		command_line_copy_all(t_command_line *command_line);
int		copy_selection_to_clipboard(t_command_line *command_line);
int		paste_current_index(t_command_line *command_line, char *to_paste);
int		delete_command_line_selection(t_command_line *command_line);

/*
** heredoc.c
*/
char	*heredoc(t_shell *shell, char *stop,
			char *(*heredoc_func)(char *), int *ret);

/*
** selection.c
*/

void	populate_min_max_selection(t_command_line *command_line,
		int *min, int *max);
void	render_command_visual(t_command_line *command_line);
#endif
