/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:41:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 14:22:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_command(t_shell *shell, char *command)
{
	t_list	*tokens;
	int		ret;

	if (sh_verbose_update(shell) == FAILURE)
		return (FAILURE);
	if ((ret = sh_lexer(command, &tokens, shell)) != SUCCESS)
		return (ret);
	if (sh_parser(tokens, shell) != SUCCESS)
		return (SUCCESS);
	// return (sh_process_traverse(shell));
	ret = sh_process_traverse(shell);
	return (ret);
}

int		sh_await_command(t_shell *shell)
{
	if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	if (sh_append_to_historic(shell,
			g_glob.command_line.dy_str->str) != SUCCESS)
		return (FAILURE);
	return (sh_process_command(shell, g_glob.command_line.dy_str->str));
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
