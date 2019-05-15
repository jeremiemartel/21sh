/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/11 19:13:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_command(t_shell *shell, char *command)
{
	t_list *tokens;

	if (sh_lexer(command, &tokens, shell) != SUCCESS)
		return (FAILURE);
	if (sh_parser(tokens, shell) != SUCCESS)
	   	return (SUCCESS);
	return (sh_process_traverse(shell));
}

int		sh_await_command(t_shell *shell)
{
	if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	if (sh_append_to_historic(shell, g_glob.command_line.dy_str->str) != SUCCESS)
		return (FAILURE);
	return (sh_process_command(shell, g_glob.command_line.dy_str->str));
}

int		main(int argc, char **argv, char **env)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	init_signals();
	if (!isatty(0))
	{
		if (sh_init_shell(&shell, env) != SUCCESS)
			return (sh_reset_shell(FAILURE));
		return (sh_process_canonical_mode(&shell));
	}
	else if (sh_init_terminal(&shell, env) != SUCCESS)
		return (FAILURE);
	if (sh_init_shell(&shell, env) != SUCCESS)
		return (sh_reset_shell(FAILURE));
	while (shell.running)
	{
		if (sh_await_command(&shell) != SUCCESS && shell.running)
		{
			sh_free_all(&shell);
			return (sh_reset_shell(FAILURE));
		}
	}
	return (sh_reset_shell(SUCCESS));
}
