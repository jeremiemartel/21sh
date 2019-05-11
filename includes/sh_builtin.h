/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/11 17:23:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

typedef	int	(*t_builtin)(t_context *);

/*
** sh_builtin.c
*/
t_builtin		sh_builtin_find(t_context *context);

/*
** builtins :
*/
int				sh_builtin_echo(t_context *context);
int				sh_builtin_exit(t_context *context);
int				sh_builtin_pwd(t_context *context);
int				sh_builtin_where(t_context *context);

#endif
