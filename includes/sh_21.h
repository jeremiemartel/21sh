/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/23 11:49:23 by jmartel          ###   ########.fr       */
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
	int				len;
	int				utf8_len;
	int				index_byte_offset;
	int				index_char_offset;
}					t_word;

typedef struct		s_file
{
	char			*name;
	char			unstatable;
	struct stat		st;
}					t_file;

typedef struct		s_auto_complete
{
	t_dlist			*choices;
	int				choices_common_len;
}					t_auto_complete;

typedef struct		s_command_line
{
	char			*prompt;
	t_dy_str		*dy_str;
	int				nb_chars;
	int				current_index;
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
	char			*clipboard;
	t_dy_tab		*assignments;
	char			running;
	struct termios	term;
	t_auto_complete	autocompletion;
	char			*to_append_to;
}					t_shell;

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
int			render_command_line(t_dy_str *dy_str, int cursor_inc);
int			sh_get_command(t_shell *shell, t_command_line *command_line);
/*
** edit_command.c
*/
void    process_left(t_command_line *command_line);
void    process_right(t_command_line *command_line);

void	process_suppr(t_command_line *command_line);
void	process_delete(t_command_line *command_line);

/*
** cursor_motion.c
*/

void	get_down_from_command(t_command_line *command_line);
int		process_clear(t_dy_str *dy_str);
void	go_up_to_prompt(int width, int cursor);
void	replace_cursor_after_render(void);


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

int		process_up(t_shell *shell, t_command_line *command_line);
int		process_down(t_shell *shell, t_command_line *command_line);
/*
** tools.c
*/
void	ring_bell(void);
void	flush_command_line(t_command_line *command_line);
int		get_file_in_dir(char *filename, char *dirname);
int		get_path_and_file_from_str(char *str, char **path, char **file);

/*
** autocompletion.c
*/
char	*get_first_word(char *str);
int		process_tab(t_shell *shell, t_command_line *command_line);
/*
** preprocess_choice_add.c
*/
int		ft_preprocess_choice_add(t_shell *shll, char *entry, t_dlist ***to_add);

/*
** populate_word_by_index.c
*/
int     populate_word_by_index(char *s, int index, t_word *word);

/*
** populate_choices_from_word.c
*/
int     populate_choices_from_word(t_dy_str *command,
 		t_shell *shell, t_word *word);

/*
** add_choices_from_dir.c
*/
int		add_choices_from_dir(t_shell *shell, t_word *word, char *dirname,
			char *prefix);

/*
** free_all.c
*/
void	free_file_dlst(void *f, size_t dummy);

/*
** process_shift.c
*/
int		process_shift_right(t_command_line *command_line);
int		process_shift_left(t_command_line *command_line);
#endif
