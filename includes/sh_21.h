/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/29 19:08:12 by ldedier          ###   ########.fr       */
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
# include "sh_command_line.h"

# include "sh_vars.h"

# define SUCCESS		0
# define FAILURE		1
# define ATTR_ERROR		2

# define CTRL_D			3
# define CTRL_C			4

# define KEEP_READ		5

# define HISTORIC_FILE	".historic"

/*
** Macros of fdin, fdout and fderr in context->fd
*/
# define FD_IN		0
# define FD_OUT		1
# define FD_ERR		2

# define CWD_LEN		1000

/*
** Pipe input and output indexes in a int[2]
*/
# define PIPE_IN		1
# define PIPE_OUT		0

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

typedef struct dirent	t_dirent;

typedef struct		s_shell
{
	t_lr_parser		parser;
	t_historic		historic;
	t_dy_tab		*env;
	t_dy_tab		*vars;
	t_list			*builtins;
	char			*clipboard;
	char			running;
	struct termios	term;
}					t_shell;

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

/*
** sanitize_path.c
*/
char		*get_sanitized_path_from_old(char *old_pwd, char *path);

int			sh_await_command(t_shell *shell);
/*
** free_all.c
*/
void		sh_free_all(t_shell *shell);
void	free_file_dlst(void *f, size_t dummy);
void	free_file(t_file *file);
void	sh_free_lr_automata(t_lr_parser *parser);
int		sh_process_command(t_shell *shell, char *command);
void	sh_free_ast_builder(t_ast_builder *ast_builder);
void	sh_free_ast_node(t_ast_node **ast_node);
void	sh_free_parser_trees(t_lr_parser *parser);

/*
** canonical_mode.c
*/
int			sh_process_canonical_mode(t_shell *shell);

/*
** process_historic.c
*/
int			sh_append_to_historic(t_shell *shell, char *command);

/*
** home.c
*/
int			process_subst_home(t_shell *shell, char **str);
char		*get_home_dup(t_shell *shell);
#endif
