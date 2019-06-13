/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 15:41:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

# include "sh_21.h"

# define DGREAT_OPT		(O_WRONLY | O_APPEND | O_CREAT)
# define GREAT_OPT		(O_WRONLY | O_TRUNC | O_CREAT)

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

typedef struct		s_command_metadata
{
	t_list			*redirections;
}					t_command_metadata;

typedef struct		s_heredoc_metadata
{
	t_redirection		redirection;
}					t_heredoc_metadata;

typedef union		u_metadata
{
	t_command_metadata	command_metadata;
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
	int				ret_value;
	t_list			**redirections;
}					t_context;

/*
********************************************************************************
*/

/*
** sh_execute.c
*/
int					sh_process_execute_close_pipes(t_context *context);
int					sh_process_execute(t_context *context);

/*
** t_context.c
*/
int					t_context_init(t_context *context, t_shell *shell);
void				t_context_free_content(t_context *context);

/*
** sh_redirections.c
*/
t_redirection		*get_redirection(
	t_redirection_type type, int redirected_fd, t_list *list);
int					sh_add_redirection(
	t_redirection_type type, int redirected_fd, int fd, t_list **list);
int					get_redirected_fd(
	t_redirection_type type, int fd, t_list *redirections);
int					sh_process_fd_aggregation(
	t_redirection_type type, int redirected_fd, int fd, t_list **redirections);

/*
** sh_debug.c
*/
void				print_redirection(t_redirection *redirection);
void				print_redirection_list(t_list *list);

/*
** sh_exec_builtin.c
*/
int					sh_exec_builtin(t_context *context);

#endif
