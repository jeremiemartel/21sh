/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:20:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/15 17:31:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_COMMAND_LINE_H
# define SH_COMMAND_LINE_H

# include "libft.h"

# define CWD_LEN			1000

# define PROMPT				""
# define BACKSLASH_PROMPT	""
# define QUOTE_PROMPT		"quote"
# define DQUOTE_PROMPT		"dquote"

# define COMMAND_PROMPT	"(command)"
# define VISUAL_PROMPT	"(visual)"
# define HEREDOC_PROMPT	"heredoc"
# define PROMPT_SUFFIX	"> "
# define READ_BUFF_SIZE	4

# define SUCCESS_RSRCH		"failing bck-i-search: "
# define UNSUCCESS_RSRCH	"bck-i-search: "

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
	E_CONTEXT_DQUOTE,
	E_CONTEXT_QUOTE,
	E_CONTEXT_BACKSLASH,
}					t_command_line_context;

typedef struct				s_searcher
{
	int						active;
	t_dlist					*head;
	t_dy_str				*dy_str;
	int						match_index;
	int						unsuccessful;
}							t_searcher;

typedef struct				s_command_line
{
	t_auto_complete 		autocompletion;
	t_searcher				searcher;
	t_dy_str				*dy_str;
	char					*heredoc_eof;
	char					*prompt;
	int						nb_chars;
	int						current_index;
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
	t_cfg			*cfg;
	int				cursor;
	struct winsize	winsize;
	int				verbose;
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
int			sh_add_to_dy_str(t_dy_str *dy_str,
				unsigned char buffer[READ_BUFF_SIZE], int nb_bytes);
int			reset_command_line(t_shell *shell, t_command_line *command_line);
int			render_command_line(t_command_line *command_line, int c, int r);
int			sh_get_command(t_shell *shell, t_command_line *command_line);

/*
** edit_command.c
*/
void    process_edit_command_left(t_command_line *command_line);
void    process_edit_command_right(t_command_line *command_line);
void	process_suppr(t_command_line *command_line);
void	process_delete(t_command_line *command_line, t_shell *shell);

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
int		get_left_w_char_index_dy_str(t_dy_str *str, int index);
/*
** is_printable_utf8.c
*/
int		is_printable_utf8(unsigned char *buffer, int nb_bytes);

/*
** keys.c
*/
int		get_keys(t_shell *shell, t_command_line *command_line);
void	print_buffer(unsigned char buffer[READ_BUFF_SIZE]);

/*
** keys_ctrl.c
*/
int		process_ctrl_c(t_shell *shell, t_command_line *command_line);
int		process_ctrl_d(t_shell *shell, t_command_line *command_line);

/*
** keys_insert.c
*/
int		process_keys_insert(unsigned char buffer[READ_BUFF_SIZE],
			t_shell *shell, t_command_line *command_line, int ret);
/*
** keys_others.c
*/
int		process_keys_others(unsigned char buffer[READ_BUFF_SIZE],
			t_shell *shell, t_command_line *command_line);

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
int		get_path_from_absolute_path(char *absolute,  char **path);

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
			char *str, t_word word, int print_choices);
int		paste_current_index(t_command_line *command_line, char *to_paste);
int		delete_command_line_selection(t_command_line *command_line);
int		command_line_nb_rows(t_command_line *command_line);
/*
** xy.c
*/
t_xy	get_position(int cursor);
int		xy_is_equal(t_xy xy1, t_xy xy2);

/*
** update_prompt.c
*/
int		process_escape(t_shell *shell, t_command_line *command_line);
int		process_i(t_shell *shell, t_command_line *command_line);
int		process_v(t_shell *shell, t_command_line *command_line);
int		update_prompt(t_shell *shell, t_command_line *command_line);
int		update_prompt_from_quote(t_shell *shell, t_command_line *command_line,
			char quote);
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
			char *(*heredoc_func)(const char *), int *ret);

/*
** selection.c
*/

void	populate_min_max_selection(t_command_line *command_line,
		int *min, int *max);
void	render_command_visual(t_command_line *command_line);

/*
** historic_research.c
*/
int		process_research_historic(t_command_line *command_line, t_shell *shell);
int		update_research_historic(t_command_line *command_line,
			t_shell *shell, int reset);
/*
** render_research.c
*/
int		render_research(t_command_line *command_line);

/*
** free_command_line.c
*/
void 	sh_free_command_line(t_command_line *command_line);

/*
** sh_process_quoted.c
*/
int		sh_process_quoted(t_lexer *lexer);

#endif
