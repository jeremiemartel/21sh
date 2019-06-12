/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 16:15:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

typedef enum		e_cd_opt
{
	e_cd_opt_logic,
	e_cd_opt_physic
}					t_cd_opt;

typedef struct		s_binary_stats
{
	int				max_path_len;
	int				max_name_len;
	int				max_hits_str_len;
}					t_binary_stats;

typedef	int	(*t_builtin)(t_context *);

typedef struct		s_builtin_container
{
	char			*name;
	t_builtin		builtin;
}					t_builtin_container;

/*
** sh_builtin.c
*/
t_builtin		sh_builtin_find(t_context *context);

# define NB_BUILTINS	11

/*
** builtins :
*/
t_builtin_container	*get_builtins(void);

int				sh_builtin_cd(t_context *context);
int				sh_builtin_echo(t_context *context);
int				sh_builtin_exit(t_context *context);
int				sh_builtin_pwd(t_context *context);
int				sh_builtin_where(t_context *context);
int				sh_builtin_verbose(t_context *context);
int				sh_builtin_set(t_context *context);
int				sh_builtin_hash(t_context *context);
int				sh_builtin_setenv(t_context *context);
int				sh_builtin_unsetenv(t_context *context);
int				sh_builtin_env(t_context *context);

/*
** sh_builtin_cd_tools.c
*/
int				end_with_char(char *str, char c);
int				ft_update_old_pwd(char *old_pwd, char *path, t_cd_opt flag,
		t_context *context);

/*
** sh_builtin_hash_stats.c
*/
void			update_hash_stats(t_hash_table *table, t_binary_stats *stats);

/*
** sh_builtin_setenv_tools.c
*/
int				sh_process_setenv_equal(char *entry, t_dy_tab *env);
#endif
