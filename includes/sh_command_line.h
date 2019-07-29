/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:20:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 11:44:10 by ldedier          ###   ########.fr       */
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

typedef char *(*t_heredoc_func)(const char *);

typedef enum		e_mode
{
	E_MODE_INSERT,
	E_MODE_VISUAL,
	E_MODE_COMMAND
}					t_mode;

typedef enum		e_cl_context
{
	E_CONTEXT_STANDARD,
	E_CONTEXT_HEREDOC,
	E_CONTEXT_DQUOTE,
	E_CONTEXT_QUOTE,
	E_CONTEXT_BACKSLASH,
}					t_cl_context;

typedef struct		s_searcher
{
	int				active;
	t_dlist			*head;
	t_dy_str		*dy_str;
	int				match_index;
	int				unsuccessful;
}					t_searcher;

typedef struct		s_command_line
{
	t_auto_complete	autocompletion;
	t_searcher		searcher;
	t_dy_str		*dy_str;
	char			*heredoc_eof;
	char			*prompt;
	int				nb_chars;
	int				current_index;
	t_mode			mode;
	int				interrupted;
	char			*clipboard;
	int				pinned_index;
	int				last_char_input;
	t_cl_context	context;
	int				to_append;
	char			*to_append_str;
}					t_command_line;

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

typedef struct		s_glob
{
	struct termios	term_init;
	struct termios	term;
	t_command_line	command_line;
	t_cfg			*cfg;
	int				cursor;
	struct winsize	winsize;
	int				verbose;
}					t_glob;

t_glob				g_glob;

/*
********************************************************************************
*/

/*
** research_historic.c
*/
int					process_find_in_historic(
	t_command_line *command_line, char *to_search_in, char *found);
int					progress_process_research_historic(
	t_command_line *command_line, t_shell *shell);
int					update_research_historic(
	t_command_line *command_line, t_shell *shell, int reset);
int					process_research_historic(
	t_command_line *command_line, t_shell *shell);

/*
** keys_others.c
*/
int					process_keys_command(
	unsigned char buffer[READ_BUFF_SIZE],
	t_shell *shell,
	t_command_line *command_line);
int					process_keys_visual(
	unsigned char buffer[READ_BUFF_SIZE],
	t_shell *shell,
	t_command_line *command_line);
int					process_keys_others(
	unsigned char buffer[READ_BUFF_SIZE],
	t_shell *shell,
	t_command_line *command_line);

/*
** sh_get_cursor_position.c
*/
int					process_read_cursor_position(
	char answer[4096], size_t *answer_len, int fd);
int					sh_get_cursor_position(int *x, int *y);

/*
** cursor_motion.c
*/
void				go_right(int right);
void				go_up_left(int up);
int					go_up_to_prompt(int width, int cursor);

/*
** render_command_line.c
*/
void				render_command_researched(
	t_command_line *command_line);
int					print_after_command_line(
	t_command_line *command_line, int print_choices);
int					render_command_line(
	t_command_line *command_line, int cursor_inc, int print_choices);

/*
** utf8_tools.c
*/
int					ft_strlen_utf8(char *str);
int					ft_strnlen_utf8(char *str, int n);
int					get_left_w_char_index_dy_str(
	t_dy_str *dy_str, int index);
int					get_left_w_char_index(t_command_line *command_line);
int					get_right_w_char_index(t_command_line *command_line);

/*
** sh_process_shift_vertical.c
*/
int					process_shift_up(t_command_line *command_line);
int					process_shift_down(t_command_line *command_line);

/*
** sh_process_shift_horizontal.c
*/
int					process_process_shift_right(
	t_command_line *c_line, t_word *word, int *index);
int					process_shift_right(t_command_line *c_line);
int					process_process_shift_left(
	t_command_line *command_line, t_word *word, int *index);
int					process_shift_left(t_command_line *command_line);

/*
** edit_command.c
*/
void				ring_bell(void);
void				process_edit_command_left(
	t_command_line *command_line);
void				process_edit_command_right(
	t_command_line *command_line);

/*
** update_prompt_keys.c
*/
int					update_prompt_cwd_home(char **new_prompt);
int					process_escape(
	t_shell *shell, t_command_line *command_line);
int					process_i(
	t_shell *shell, t_command_line *command_line);
int					process_v(
	t_shell *shell, t_command_line *command_line);

/*
** sh_process_historic.c
*/
int					process_historic_down(
	t_shell *shell, t_command_line *command_line);
int					process_historic_up(
	t_shell *shell, t_command_line *command_line);

/*
** update_prompt.c
*/
int					update_prompt_from_absolute_path(
	char *cwd, char **new_prompt);
int					update_prompt_cwd(t_shell *shell, char **new_prompt);
int					update_prompt_context(
	t_shell *shell, t_command_line *command_line, char **new_prompt);
int					update_prompt(
	t_shell *shell, t_command_line *command_line);
int					update_prompt_from_quote(
	t_shell *shell, t_command_line *command_line, char quote);

/*
** selection.c
*/
void				populate_min_max_selection(
	t_command_line *command_line, int *min, int *max);
void				render_command_visual(t_command_line *command_line);

/*
** sh_command_line_tools.c
*/
void				print_eof_delimiter(void);
int					sh_add_eof(int interrupted);

/*
** keys_ctrl.c
*/
int					process_ctrl_c(
	t_shell *shell, t_command_line *command_line);
int					process_ctrl_d(
	t_shell *shell, t_command_line *command_line);

/*
** is_printable_utf8.c
*/
int					is_utf8_len_header(
	unsigned char first_byte, int length);
int					is_utf8_next_byte(unsigned char next_byte);
int					is_utf8_len_3(unsigned char *buffer);
int					is_utf8_len_4(unsigned char *buffer);
int					is_printable_utf8(unsigned char *buffer, int nb_bytes);

/*
** sh_delete_command.c
*/
void				process_delete_searcher(
	t_command_line *command_line, t_shell *shell);
void				process_process_delete(t_command_line *command_line);
void				process_delete(
	t_command_line *command_line, t_shell *shell);
void				process_suppr(t_command_line *command_line);

/*
** keys.c
*/
void				print_buffer(unsigned char buffer[READ_BUFF_SIZE]);
int					process_escape_sequence(
	t_shell *shell,
	t_command_line *command_line,
	unsigned char buffer[READ_BUFF_SIZE]);
void				process_shift(
	t_command_line *command_line,
	unsigned char buffer[READ_BUFF_SIZE]);
int					process_keys(
	t_shell *shell,
	t_command_line *command_line,
	unsigned char *buffer);
int					get_keys(t_shell *shell, t_command_line *command_line);

/*
** heredoc.c
*/
int					process_heredoc_through_command(
	char **res,
	t_shell *shell,
	t_heredoc_func heredoc_func,
	t_command_line *command_line);
void				init_heredoc_command_line(
	t_shell *shell, t_command_line *command_line, char *stop);
char				*heredoc(
	t_shell *shell,
	char *stop,
	t_heredoc_func heredoc_func,
	int *ret);

/*
** xy.c
*/
t_xy				get_position(int cursor);
int					xy_is_equal(t_xy xy1, t_xy xy2);

/*
** keys_insert.c
*/
int					process_enter_no_autocompletion(
	t_command_line *command_line);
int					process_enter(t_command_line *command_line);
int					process_keys_ret(
	t_shell *shell,
	t_command_line *command_line,
	unsigned char *buffer);
int					process_key_insert_printable_utf8(
	unsigned char buffer[READ_BUFF_SIZE],
	t_shell *shell,
	t_command_line *command_line,
	int ret);
int					process_keys_insert(
	unsigned char buffer[READ_BUFF_SIZE],
	t_shell *shell,
	t_command_line *command_line,
	int ret);

/*
** get_command.c
*/
int					sh_add_to_dy_str(
	t_dy_str *dy_str,
	unsigned char buffer[READ_BUFF_SIZE],
	int nb_bytes);
int					sh_add_to_command(
	t_command_line *command_line,
	unsigned char buffer[READ_BUFF_SIZE],
	int nb_bytes);
int					reset_command_line(
	t_shell *shell, t_command_line *command_line);
int					sh_get_command(
	t_shell *shell, t_command_line *command_line);

/*
** render_research.c
*/
int					render_research(t_command_line *command_line);

/*
** command_line.c
*/
void				flush_command_line(t_command_line *command_line);
int					process_substitute_command(
	t_command_line *command_line,
	char *str,
	t_word word,
	int print_choices);
int					substitute_current_index(
	t_command_line *command_line, t_file *file);
int					command_line_nb_rows(t_command_line *command_line);

/*
** arrows.c
*/
int					process_down(
	t_shell *shell, t_command_line *command_line);
int					process_up(
	t_shell *shell, t_command_line *command_line);
int					process_left(
	t_shell *shell, t_command_line *command_line);
int					process_right(
	t_shell *shell, t_command_line *command_line);

/*
** cursor_tools.c
*/
int					get_true_cursor_pos(int cursor);
int					get_down_from_command(t_command_line *command_line);
void				replace_cursor_on_index(void);
void				replace_cursor_after_render(void);
int					process_clear(t_command_line *command_line);

/*
** sh_clipboard.c
*/
int					process_clipboard_line_nl(
	t_shell *shell, t_command_line *command_line, char *str);
int					process_clipboard_line(
	t_shell *shell, t_command_line *command_line, t_gnl_info *info);
int					process_clipboard_from_fd(
	t_shell *shell, int fd, t_command_line *command_line);
int					process_clipboard_son(int fds[2], char *pbpaste_path);
int					process_clipboard_shell(
	t_shell *shell, t_command_line *command_line);

/*
** home_end.c
*/
int					process_end(t_command_line *command_line);
int					process_start(t_command_line *command_line);

/*
** sh_process_quoted.c
*/
int					sh_process_process_quoted(
	int old_context, t_lexer *lexer);
int					sh_process_quoted(t_lexer *lexer);

/*
** copy_paste_delete.c
*/
int					command_line_copy_all(t_command_line *command_line);
int					copy_selection_to_clipboard(
	t_command_line *command_line);
int					paste_current_index(
	t_command_line *command_line, char *to_paste);
int					delete_command_line_selection(
	t_command_line *command_line);

/*
** free_command_line.c
*/
void				sh_free_command_line(t_command_line *command_line);

#endif
