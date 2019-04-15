/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/14 15:37:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_await_command(t_shell *shell)
{
	t_list *tokens;

	if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	if (lexer(g_glob.command_line.dy_str->str, &tokens, shell->env) != SUCCESS)
		return (FAILURE);
	if (sh_parser(tokens, shell))
	   	return (FAILURE);
	return (sh_process_traverse(shell));
}

int		main(int argc, char **argv, char **env)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	init_signals();
	if (sh_init_terminal(&shell, env) != SUCCESS)
		return (FAILURE);
	if (sh_init_shell(&shell, env) != SUCCESS)
		return (FAILURE);
	while (shell.running)
	{
		if (sh_await_command(&shell) != SUCCESS && shell.running)
		{
			sh_free_all(&shell);
			return (sh_reset_shell(ERROR));
		}
	}
	return (sh_reset_shell(SUCCESS));
}
