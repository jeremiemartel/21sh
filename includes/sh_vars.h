/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vars.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:35:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/20 16:25:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_VARS_H
# define SH_VARS_H

# define VERBOSE_AST		0x0001
# define VERBOSE_LEXER		0x0002
# define VERBOSE_EXEC		0x0004
# define VERBOSE_PIPE		0x0008
# define VERBOSE_EXPANSION	0x0010
# define VERBOSE_BUILTIN	0x0020
# define VERBOSE_TRAVERSE	0x0040

/*
********************************************************************************
*/

/*
** sh_vars_tools_1.c
*/
int		sh_vars_key_exist(t_dy_tab *vars, char *key);
int		sh_vars_get_index(t_dy_tab *vars, char *key);
char	*sh_vars_get_value(t_dy_tab *env, t_dy_tab *vars, char *key);

/*
** sh_env.c
*/
void	sh_env_update_ret_value_wait_result(t_shell *shell, int res);
void	sh_env_update_ret_value(t_shell *shell, int res);
int		sh_env_update_status_and_question(t_shell *shell, int res);
int		sh_env_update_question_mark(t_shell *shell);

/*
** sh_vars_tools_2.c
*/
int		sh_vars_mod_key(t_dy_tab *vars, char *key, char *value);
int		sh_vars_add_key(t_dy_tab *vars, char *key, char *value);
int		sh_vars_assignment(
	t_dy_tab *env, t_dy_tab *vars, char *assignment);
int		sh_vars_assign_key_val(
	t_dy_tab *env, t_dy_tab *vars, char *key, char *value);

/*
** sh_verbose_check.c
*/
int		sh_verbose_ast(void);
int		sh_verbose_lexer(void);
int		sh_verbose_exec(void);
int		sh_verbose_pipe(void);
int		sh_verbose_expansion(void);
int		sh_verbose_builtin(void);
int		sh_verbose_traverse(void);

/*
** sh_verbose.c
*/
void	sh_verbose_update(t_shell *shell);

/*
** sh_env_tools.c
*/
char	*sh_env_get_value(char **env, char *str);

#endif
