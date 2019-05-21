/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/21 18:04:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

typedef enum		e_cd_opt
{
	e_cd_opt_logic,
	e_cd_opt_physic
}					t_cd_opt;

typedef	int	(*t_builtin)(t_context *);

/*
** sh_builtin.c
*/
t_builtin		sh_builtin_find(t_context *context);

/*
** builtins :
*/
int				sh_builtin_cd(t_context *context);
int				sh_builtin_echo(t_context *context);
int				sh_builtin_exit(t_context *context);
int				sh_builtin_pwd(t_context *context);
int				sh_builtin_where(t_context *context);
int				sh_builtin_verbose(t_context *context);
int				sh_builtin_set(t_context *context);

/*
** sh_builtin_cd_tools.c
*/
int				end_with_char(char *str, char c);
int				ft_update_old_pwd(char *old_pwd, char *path, t_cd_opt flag,
					t_context *context);
#endif
