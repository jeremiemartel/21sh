/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_verbose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:16:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 11:14:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_verbose_ast(void)
{
	if (g_glob.verbose & VERBOSE_AST)
		return (1);
	return (0);
}

int		sh_verbose_lexer(void)
{
	if (g_glob.verbose & VERBOSE_LEXER)
		return (1);
	return (0);
}

int		sh_verbose_exec(void)
{
	if (g_glob.verbose & VERBOSE_EXEC)
		return (1);
	return (0);
}

int		sh_verbose_pipe(void)
{
	if (g_glob.verbose & VERBOSE_PIPE)
		return (1);
	return (0);
}

int		sh_verbose_expansion(void)
{
	if (g_glob.verbose & VERBOSE_EXPANSION)
		return (1);
	return (0);
}

int		sh_verbose_update(t_shell *shell)
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

	if ((value = sh_vars_get_value(shell->env, shell->vars,
			"verbose_pipe")) && *value)
		g_glob.verbose += g_glob.verbose & VERBOSE_PIPE ? 0 : VERBOSE_PIPE;
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_PIPE ? VERBOSE_PIPE : 0;

	if ((value = sh_vars_get_value(shell->env, shell->vars, "verbose_expansion")) && *value)
		g_glob.verbose += g_glob.verbose & VERBOSE_EXPANSION ? 0 : VERBOSE_EXPANSION;
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_EXPANSION ? VERBOSE_EXPANSION : 0;
	return (SUCCESS);
}
