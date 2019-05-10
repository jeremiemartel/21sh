/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 17:51:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

//To destroy
typedef struct	s_builtin
{
	char	*name;
	int		(*builtin)(t_dy_tab *argv, t_dy_tab *env);
}				t_builtin;


/*
** sh_builtin.c
*/
t_list			*sh_builtin_init_list(void);

/*
** builtins :
*/
int				sh_builtin_echo(t_context *context);
int				sh_builtin_exit(t_dy_tab *argv, t_dy_tab *env);
int				sh_builtin_pwd(t_dy_tab *argv, t_dy_tab *env);


/*
** t_builtin.c
*/
t_builtin		*t_builtin_new(char *name,
					int (*builtin)(t_dy_tab *argv, t_dy_tab *env));
void			t_builtin_free(t_builtin *built);
void			t_builtin_free_list(t_list *built_lst);

#endif