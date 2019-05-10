/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 19:05:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

/*
** sh_builtin.c
*/
int				sh_builtin_find(t_context *context);

/*
** builtins :
*/
int				sh_builtin_echo(t_context *context);
int				sh_builtin_exit(t_context *context);
int				sh_builtin_pwd(t_context *context);

#endif