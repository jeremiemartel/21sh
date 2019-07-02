/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_verbose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:16:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 21:57:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_verbose_update_2(t_shell *shell)
{
	char	*value;
	int		buffer;

	if ((value = sh_vars_get_value(shell->env, shell->vars,
			"verbose_pipe")) && *value)
		g_glob.verbose += g_glob.verbose & VERBOSE_PIPE ? 0 : VERBOSE_PIPE;
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_PIPE ? VERBOSE_PIPE : 0;
	if ((value = sh_vars_get_value(shell->env, shell->vars,
		"verbose_expansion")) && *value)
	{
		buffer = g_glob.verbose & VERBOSE_EXPANSION ? 0 : VERBOSE_EXPANSION;
		g_glob.verbose += buffer;
	}
	else
	{
		buffer = g_glob.verbose & VERBOSE_EXPANSION ? VERBOSE_EXPANSION : 0;
		g_glob.verbose -= buffer;
	}
	return (SUCCESS);
}

int			sh_verbose_update(t_shell *shell)
{
	char	*value;

	if ((value = sh_vars_get_value(shell->env, shell->vars,
			"verbose_ast")) && *value)
		g_glob.verbose += g_glob.verbose & VERBOSE_AST ? 0 : VERBOSE_AST;
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_AST ? VERBOSE_AST : 0;
	if ((value = sh_vars_get_value(shell->env, shell->vars,
			"verbose_lexer")) && *value)
		g_glob.verbose += g_glob.verbose & VERBOSE_LEXER ? 0 : VERBOSE_LEXER;
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_LEXER ? VERBOSE_LEXER : 0;
	if ((value = sh_vars_get_value(shell->env, shell->vars,
			"verbose_exec")) && *value)
		g_glob.verbose += g_glob.verbose & VERBOSE_EXEC ? 0 : VERBOSE_EXEC;
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_EXEC ? VERBOSE_EXEC : 0;
	return (sh_verbose_update_2(shell));
}
