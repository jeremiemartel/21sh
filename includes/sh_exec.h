/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 17:20:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

/*
** sh_execute.c
*/
int		sh_execute_command_no_path(t_context *context);
int		sh_execute_command_path(t_context *context, char *path_str);
int		sh_execute_command(t_context *context);

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
