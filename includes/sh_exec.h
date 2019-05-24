/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/24 12:45:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

typedef struct		s_context
{
	t_shell			*shell;
	struct termios	*term;
	t_dy_tab		*env;
	t_dy_tab		*vars;
	char			*path;
	t_dy_tab		*params; //argv
	int				(*builtin)(t_context *context);
	int				father_id;
	int				fd[3];
	int				pipe[2];
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

#endif
