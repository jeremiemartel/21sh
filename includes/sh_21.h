/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/23 12:38:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H


#include <stdio.h>

# include <stdarg.h>
# include <termcap.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

/*
** read(2)
*/
# include <fcntl.h>

# include "libft.h"
# include "perror.h"
# include "sh_tokens.h"
# include "sh_grammar.h"
# include "sh_autocompletion.h"
# include "sh_parser.h"
# include "sh_lexer.h"
# include "sh_exec.h"
# include "sh_builtin.h"
# include "sh_traverse.h"
# include "sh_traverse_tools.h"

# include "vars.h"

# define SUCCESS		0
# define FAILURE		1
# define ATTR_ERROR		2
# define CTRL_D			3

/*
** Macros of fdin, fdout and fderr in context->fd
*/
#define FD_IN		0
#define FD_OUT		1
#define FD_ERR		2

/*
** Pipe input and output indexes in a int[2]
*/
#define PIPE_IN		1
#define PIPE_OUT	0

# define PROMPT			"$21_sh(to_rework)> "
# define COMMAND_PROMPT	"$21_sh(to_rework(command))> "
# define VISUAL_PROMPT	"$21_sh(to_rework(visual))> "
# define HISTORIC_FILE	".historic"
# define READ_BUFF_SIZE	4
# define CWD_LEN		1000

/*
** Colors macros
*/
# define COLOR_BLACK	"\033[1;30m"
# define COLOR_RED		"\033[1;31m"
# define COLOR_GREEN	"\033[1;32m"
# define COLOR_YELLOW	"\033[1;33m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_PINK		"\033[1;35m"
# define COLOR_CYAN		"\033[1;36m"
# define COLOR_GREY		"\033[1;37m"
# define COLOR_END		"\033[1;0m"

/*
** ANSI color constants
*/
# define RED        "\x1B[31m"
# define GREEN      "\x1B[32m"
# define YELLOW     "\x1B[33m"
# define BLUE       "\x1B[34m"
# define MAGENTA    "\x1B[35m"
# define CYAN       "\x1B[36m"
# define WHITE      "\x1B[37m"
# define L_GREY     "\x1B[90m"
# define L_BLUE     "\x1B[94m"
# define L_MAGENTA  "\x1B[95m"
# define L_CYAN     "\x1B[96m"
# define L_GREEN    "\e[1;32m"
# define BRED       "\x1B[41m"
# define BGREEN     "\x1B[42m"
# define BYELLOW    "\x1B[43m"
# define BBLUE      "\x1B[44m"
# define BMAGENTA   "\x1B[44m"
# define BCYAN      "\x1B[46m"
# define BWHITE     "\x1B[47m"
# define BL_BLUE    "\x1B[104m"
# define BL_MAGENTA "\x1B[105m"
# define BL_CYAN    "\x1B[106m"
# define BOLD       "\x1b[1m"
# define UNDERLINE  "\x1b[4m"
# define EOC        "\033[0m"

typedef enum		e_mode
{
	E_MODE_INSERT,
	E_MODE_VISUAL,
	E_MODE_COMMAND
}					t_mode;

typedef struct		s_command_line
{
	char			*prompt;
	t_dy_str		*dy_str;
	int				nb_chars;
	int				current_index;
	t_auto_complete autocompletion;
	t_mode			mode;
	char			*clipboard;
	int				pinned_index;
	int				last_char_input;
}					t_command_line;

typedef struct		s_historic
{
	t_dlist			*head;
	t_dlist			*commands;
	t_dlist			head_start;
}					t_historic;

typedef struct		s_shell
{
	t_lr_parser		parser;
	t_historic		historic;
	t_dy_tab		*env;
	t_dy_tab		*vars;
	t_list			*builtins;
	char			*clipboard;
	t_dy_tab		*assignments;
	char			running;
	struct termios	term;
}					t_shell;

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
** init.c
*/

int			sh_init_shell(t_shell *shell, char **env);

int			sh_init_terminal(t_shell *shell, char **env);
void		init_signals(void);

/*
** index.c
*/
int			sh_index(t_symbol_id id);
int			is_key_of_entry(char *entry, char *key);

/*
** free_all.c
*/
void		sh_free_all(t_shell *shell);

/*
** shell_tools.c
*/

int			sh_reset_shell(int ret);
int			putchar_int(int i);
void		move(int x, int y);
int			clear_all(void);

/*
** env.c
*/
int			is_key_of_entry(char *entry, char *key);
char		*get_env_value(char **env, char *str);
char		*get_env_entry(char **env, char *str);
int			process_ms_env(t_dy_tab *env);


/*
** set_env.c
*/
int			sh_add_to_env(t_dy_tab *env, char *key, char *value);
int			sh_add_to_command(t_command_line *command,
				unsigned char buffer[READ_BUFF_SIZE], int nb_bytes);

int			sh_await_command(t_shell *shell);
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
** process_execute.c
*/
void	transmit_sig(int signal);
void	transmit_sig_and_die(int signal);
int		sh_process_execute(char *path, t_context *context);

/*
** execute.c
*/
int		sh_execute_command(t_context *context);
int		sh_execute_command_path(t_context *context, char *path_str);
int		sh_execute_command_no_path(t_context *context);
/*
** execute_tools.c
*/

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
** free_all.c
*/
void	free_file_dlst(void *f, size_t dummy);

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
** selection.c
*/

void	populate_min_max_selection(t_command_line *command_line,
		int *min, int *max);
void	render_command_visual(t_command_line *command_line);

void	free_file(t_file *file);
#endif
