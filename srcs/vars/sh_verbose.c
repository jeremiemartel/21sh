/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_verbose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:16:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/14 15:03:30 by jmartel          ###   ########.fr       */
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
	{
		ft_dprintf(2, "Lexer is in verbose mode\n");
		return (1);
	}
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

int		sh_verbose_update(t_shell *shell)
{
	char	*value;

	ft_dprintf(2, "Updating verbose mode\n");
	if ((value = sh_vars_get_value(shell->env, shell->vars, "verbose_ast")) && *value)
		g_glob.verbose += ~(g_glob.verbose & VERBOSE_AST);
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_AST;

	if ((value = sh_vars_get_value(shell->env, shell->vars, "verbose_lexer")) && *value)
		g_glob.verbose += ~(g_glob.verbose & VERBOSE_LEXER);
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_EXEC;

	if ((value = sh_vars_get_value(shell->env, shell->vars, "verbose_exec")) && *value)
		g_glob.verbose += ~(g_glob.verbose & VERBOSE_EXEC);
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_EXEC;

	if ((value = sh_vars_get_value(shell->env, shell->vars, "verbose_pipe")) && *value)
		g_glob.verbose += ~(g_glob.verbose & VERBOSE_PIPE);
	else
		g_glob.verbose -= g_glob.verbose & VERBOSE_PIPE;

	return (SUCCESS);
}
