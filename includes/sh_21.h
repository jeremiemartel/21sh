/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:48:56 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/30 15:55:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

# include <stdio.h>

# include <stdarg.h>
# include <termcap.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

/*
** wait(2)
*/
# include <sys/wait.h>

/*
** read(2)
*/
# include <fcntl.h>

# include "libft.h"
# include "sh_perror.h"
# include "sh_tokens.h"
# include "sh_parser.h"
# include "sh_productions.h"
# include "sh_grammar.h"
# include "sh_autocompletion.h"
# include "sh_lexer.h"
# include "sh_exec.h"
# include "sh_builtin.h"
# include "sh_traverse.h"
# include "sh_traverse_tools.h"
# include "sh_command_line.h"
# include "sh_expansions.h"
# include "sh_vars.h"

# define SUCCESS		0
# define ERROR			1
# define FAILURE		2
# define ATTR_ERROR		3
# define STOP_CMD_LINE	4

# define CTRL_D			5
# define CTRL_C			6

# define KEEP_READ		7

# define HISTORIC_FILE	".historic"

# define MAX_LEN_HISTORIC_ENTRY	500000
# define BINARIES_TABLE_SIZE	100

/*
** Macros of fdin, fdout and fderr in context->fd
*/
# define FD_IN		0
# define FD_OUT		1
# define FD_ERR		2

# define CWD_LEN		1000
# define NB_OPERATIONS	12

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

/*
** Activate or not bonuses that require forbidden functions
*/

# define BONUS_HOME_AS_TILDE_PROMPT	1
# define BONUS_DOLLAR_VARIABLE		1
# define BONUS_TILDE_EXP			1

typedef struct s_shell		t_shell;

struct				s_shell
{
	t_lr_parser		parser;
	t_historic		historic;
	t_dy_tab		*env;
	t_dy_tab		*vars;
	t_hash_table	*binaries;
	char			running;
	struct termios	term;
	int				ret_value_set;
	int				ret_value;
};

/*
********************************************************************************
*/

/*
** free_all.c
*/
void				sh_free_binary(t_binary *binary);
void				sh_free_binary_lst(void *b, size_t dummy);
void				free_file(t_file *file);
void				free_file_dlst(void *f, size_t dummy);
void				sh_free_all(t_shell *shell);

/*
** index.c
*/
int					sh_index_4(t_symbol_id id);
int					sh_index_3(t_symbol_id id);
int					sh_index_2(t_symbol_id id);
int					sh_index(t_symbol_id id);

/*
** init_tabs.c
*/
int					sh_update_shell_lvl(t_shell *shell);
int					sh_main_init_env(t_shell *shell, char **env);
int					sh_main_init_vars(t_shell *shell);

/*
** check_term.c
*/
char				**get_operations(void);
int					sh_check_term(void);

/*
** shell_tools.c
*/
int					putchar_int(int i);
int					sh_reset_shell(int ret);
int					sh_set_shell_back(int ret);
int					sh_set_shell(struct termios term, int ret);
int					clear_all(void);

/*
** init.c
*/
char				*refine_historic_entry(char *entry);
int					process_read_historic(
	t_historic *historic, char *line);
int					sh_init_historic(t_historic *historic);
int					sh_init_command_line(
	t_shell *shell, t_command_line *command_line);
int					sh_init_shell(t_shell *shell, char **env);

/*
** canonical_mode.c
*/
int					sh_process_canonical_mode(t_shell *shell, char **env);

/*
** tools.c
*/
int					end_with_char(char *str, char c);
int					get_file_in_dir(char *filename, char *dirname);
int					get_path_from_absolute_path(char *str, char **path);
int					get_path_and_file_from_str(
	char *str, char **path, char **file);

/*
** signals.c
*/
void				transmit_sig_and_die(int signal);
void				default_sig(int sgnl);
void				handle_resize(int signal);
void				init_signal_transmit_sig_and_die(void (*default_func)(int));
void				reset_signals();
void				init_signals(void);

/*
** init_term.c
*/
int					sh_init_terminal_database(char **env);
int					sh_init_terminal(t_shell *shell, char **env);

/*
** home.c
*/
char				*get_home_dup(t_shell *shell);
int					process_subst_home(t_shell *shell, char **str);

/*
** non_canonical_mode.c
*/
int					sh_process_command(t_shell *shell, char *command);
int					sh_process_received_command(
	t_shell *shell, t_command_line *command_line);
int					sh_await_command(t_shell *shell);
int					sh_process_noncanonical_mode(t_shell *shell);

/*
** historic.c
*/
int					sh_append_to_historic(t_shell *shell, char *command);

/*
** hash_binaries.c
*/
t_binary			*sh_new_binary(char *path, char *name);
int					compare_str_to_binary(void *str, void *binary);
int					sh_update_hash_table(
	t_shell *shell, char *path, char *name);

/*
** signal_tools.c
*/
void				transmit_sig(int signal);
void				transmit_sig_and_exit(int signal);
void				handle_stp(int sgnl);
void				handle_cont(int sgnl);

/*
** main.c
*/
int					main(int argc, char **argv, char **env);

/*
** sanitize_path.c
*/
char				*ft_get_previous_directory(char *current_directory);
char				*get_first_path_from_path(char **path);
int					add_to_path_dot_dot(char **old_path);
int					add_to_path_pwd(char **old_path, char *partial_path);
char				*get_sanitized_path_from_old(
	char *old_pwd, char *path);

#endif
