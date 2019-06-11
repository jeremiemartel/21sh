/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 10:38:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# define NB_BUILTINS	7

typedef enum		e_cd_opt
{
	e_cd_opt_logic,
	e_cd_opt_physic
}					t_cd_opt;

typedef	int	(*t_builtin)(t_context *);

typedef struct		s_builtin_container
{
	char			*name;
	t_builtin		builtin;
}					t_builtin_container;

/*
********************************************************************************
*/

/*
** sh_builtin.c
*/
t_builtin_container	*get_builtins(void);
t_builtin			sh_builtin_find(t_context *context);

/*
** sh_builtin_cd.c
*/
int					ft_process_cd(
	char *path, t_cd_opt flag, t_context *context);
int					ft_process_cd_args(
	t_context *context, int flag, int i);
int					sh_builtin_cd(t_context *context);

/*
** sh_builtin_echo.c
*/
int					sh_builtin_echo(t_context *context);

/*
** sh_builtin_set.c
*/
int					sh_builtin_set(t_context *context);

/*
** sh_builtin_exit.c
*/
int					sh_builtin_exit(t_context *context);

/*
** sh_builtin_cd_tools.c
*/
int					end_with_char(char *str, char c);
char				*get_path_from_request(char *old_pwd, char *path);
int					ft_update_old_pwd(
	char *old_pwd, char *path, t_cd_opt flag, t_context *context);

/*
** sh_builtin_pwd.c
*/
int					sh_builtin_pwd(t_context *context);

/*
** sh_builtin_where.c
*/
int					sh_builtin_where(t_context *context);

/*
** sh_builtin_verbose.c
*/
int					sh_builtin_verbose(t_context *context);

#endif
