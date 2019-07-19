/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/19 11:17:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

# include "sh_21.h"

# define DGREAT_OPT			(O_WRONLY | O_APPEND | O_CREAT)
# define GREAT_OPT			(O_WRONLY | O_TRUNC | O_CREAT)
# define EXIT_STATUS(res)	res >> 8

static pid_t g_parent = 0;

typedef enum		e_redirection_type
{
	INPUT,
	OUTPUT
}					t_redirection_type;

typedef struct		s_redirection
{
	t_redirection_type	type;
	int					redirected_fd;
	int					fd;
}					t_redirection;

typedef struct		s_pipe_metadata
{
	t_list			*contexts;
}					t_pipe_metadata;

typedef struct		s_command_metadata
{
	t_list			*redirections;
	int				should_exec;
}					t_command_metadata;

typedef struct		s_heredoc_metadata
{
	t_redirection		redirection;
}					t_heredoc_metadata;

typedef union		u_metadata
{
	t_command_metadata	command_metadata;
	t_pipe_metadata		pipe_metadata;
	t_heredoc_metadata	heredoc_metadata;
}					t_metadata;

typedef enum		e_phase
{
	E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS,
	E_TRAVERSE_PHASE_EXPANSIONS,
	E_TRAVERSE_PHASE_REDIRECTIONS,
	E_TRAVERSE_PHASE_EXECUTE
}					t_phase;

typedef struct		s_context
{
	t_shell			*shell;
	struct termios	*term;
	t_dy_tab		*env;
	t_dy_tab		*vars;
	char			*path;
	t_dy_tab		*params;
	int				(*builtin)(struct s_context *);
	int				redirected_fd;
	int				fd[3];
	t_phase			phase;
	t_ast_node		*current_command_node;
	t_ast_node		*current_pipe_sequence_node;
	t_list			**redirections;
	pid_t			pid;
	int				ret_value;
	int				ret_value_set;
}					t_context;

/*
********************************************************************************
*/

/*
** sh_execute.c
*/

int					sh_process_process_execute(t_context *context);
int					sh_add_to_pipe_sequence(t_context *context);
int					sh_process_execute(t_context *context);

/*
** sh_execute_tools.c
*/
void				sh_close_all_other_contexts(
	t_context *context, t_list *contexts);
void				sh_execute_child_builtin(
	t_context *context, t_list *contexts);
void				sh_execute_child_binary(
	t_context *context, t_list *contexts);
void				sh_execute_child(t_context *context, t_list *contexts);

/*
** sh_debug.c
*/
void				print_redirection(t_redirection *redirection);
void				print_redirection_list(t_list *list);

/*
** sh_execute_pipes.c
*/
int					sh_process_execute_dup_pipes(t_context *context);
int					sh_process_execute_close_pipes(t_context *context);

/*
** sh_exec_builtin.c
*/
int					sh_exec_builtin(t_context *context);

/*
** t_context.c
*/
void				sh_free_context_dup_lst(void *c, size_t dummy);
t_context			*t_context_dup(t_context *context);
int					t_context_init(t_context *context, t_shell *shell);
void				t_context_free_content(t_context *context);

/*
** sh_redirections.c
*/
t_redirection		*get_redirection(
	t_redirection_type type, int redirected_fd, t_list *list);
int					sh_add_redirection(
	t_redirection redirection, t_list **list);
int					get_redirected_fd(
	t_redirection_type type, int fd, t_list *redirections);
int					sh_process_fd_aggregation(
	t_redirection_type type,
	int redirected_fd,
	int fd,
	t_list **redirections);
t_redirection		sh_new_redir(
	t_redirection_type type, int redirected_fd, int fd);

/*
** sh_execute_pipe_sequence.c
*/
void				sh_process_execute_close_pipes_list(t_list *contexts);
int					sh_process_pipe_exec_fork(t_list *contexts);
int					sh_process_pipe_sequence_execute(
		t_context *context, t_list *contexts);
#endif
