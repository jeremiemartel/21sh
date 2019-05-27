/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/27 18:32:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

typedef enum			e_redirection_type
{
	INPUT,
	OUTPUT
}						t_redirection_type;

/*
**
**                       **Files Redirections**
**
** ls -la missing_file 2> file.txt
**
** type				-> OUTPUT
** redirected_fd	-> 2
** fd				-> open("file.txt", O_CREAT | O_TRUNC);
**
** ./test 2< file.txt
**
** redirected_fd	-> 2
** fd				-> open("file.txt", O_CREAT | O_TRUNC);
**
** ./test <-
**
** type				-> INPUT
** redirected_fd	-> 0
** fd				-> -1
**
**                             **Pipes**
**
** ls | cat 
**
** || pipe(int tab[2])
**
** type				-> OUTPUT		|| type				-> INPUT
** redirected_fd	-> 1			|| redirected_fd	-> 0
** fd				-> tab[1]		|| fd				-> tab[0]
*/

typedef struct			s_redirection
{
	t_redirection_type	type; 
	int					redirected_fd;
	int					fd;
}						t_redirection;

typedef struct			s_command_metadata
{
	t_list				*redirections;
}						t_command_metadata;

typedef struct			s_heredoc_metadata
{
	t_redirection		redirection;
}						t_heredoc_metadata;

typedef union			u_metadata
{
	t_command_metadata	command_metadata;
	t_heredoc_metadata	heredoc_metadata;
}						t_metadata;

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
	t_dy_tab		*params; //argv
	int				(*builtin)(t_context *context);
	int				redirected_fd;
	int				fd[3];
	t_phase			phase;
	t_ast_node		*current_command_node;
	t_list			**redirections;
}					t_context;

/*
** sh_execute.c
*/
int		sh_execute_command_no_path(t_context *context);
int		sh_execute_command_path(t_context *context);
int		sh_execute_command(t_context *context);

/*
** process_execute.c
*/
void	transmit_sig(int signal);
void	transmit_sig_and_die(int signal);
int		sh_process_execute(t_context *context);

/*
** sh_execute_tools.c
*/
int		sh_process_execute_builtin(t_context *context);
int		sh_check_execute(char *full_path, char *command_name);

/*
** t_context.c
*/
int		t_context_init(t_context *context, t_shell *shell);
void	t_context_free(t_context *context);

/*
** sh_redirections.c
*/
int		sh_add_redirection(t_redirection_type type,
			int redirected_fd, int fd, t_list **list);
/*
** debug.c
*/
void	print_redirection(t_redirection *redirection);
void	print_redirection_list(t_list *list);

#endif
