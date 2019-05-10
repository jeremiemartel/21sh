/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 18:07:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

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
int		sh_check_execute(char *full_path, char *command_name);


/*
** t_context.c
*/
int		t_context_init(t_context *context, t_shell *shell);
void	t_context_free(t_context *context);

#endif
