/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:41:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/21 15:12:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_command(t_shell *shell, char *command)
{
	t_list	*tokens;
	int		ret;

	sh_verbose_update(shell);
	ret = 0;
	if (!ret && (ret = sh_lexer(command, &tokens, shell)) != SUCCESS)
		sh_env_update_ret_value_and_question(shell, ret);
	if (!ret && (ret = sh_parser(tokens, shell)))
		sh_env_update_ret_value_and_question(shell, ret);
	if (!ret)
		ret = sh_process_traverse(shell);
	return (ret);
}

int		sh_process_received_command(t_shell *shell,
			t_command_line *command_line)
{
	if (sh_append_to_historic(shell,
			command_line->dy_str->str) != SUCCESS)
		return (FAILURE);
	return (sh_process_command(shell, command_line->dy_str->str));
}

int		sh_await_command(t_shell *shell)
{
	int		ret;

	if ((ret = sh_get_command(shell, &g_glob.command_line) != SUCCESS))
		return (ret);
	return (sh_process_received_command(shell,
		&g_glob.command_line));
}

int		sh_process_noncanonical_mode(t_shell *shell)
{
	while (shell->running)
	{
		if (sh_await_command(shell) == FAILURE)
		{
			sh_free_all(shell);
			return (sh_reset_shell(FAILURE));
		}
	}
	sh_free_all(shell);
	return (sh_reset_shell(SUCCESS));
}
