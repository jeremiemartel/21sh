/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:41:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/05 15:41:50 by ldedier          ###   ########.fr       */
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
	{
		if (ret == LEX_ERR)
			return (FAILURE);
		else
			return (SUCCESS);
	}
	else
	{	
		if (sh_parser(tokens, shell) != SUCCESS)
		   	return (SUCCESS);
		return (sh_process_traverse(shell));
	}
	return (SUCCESS);
}

int		sh_await_command(t_shell *shell)
{
	if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	if (sh_append_to_historic(shell, g_glob.command_line.dy_str->str) != SUCCESS)
		return (FAILURE);
	return (sh_process_command(shell, g_glob.command_line.dy_str->str));
}

int		sh_process_noncanonical_mode(t_shell *shell)
{
	while (shell->running)
	{
		if (sh_await_command(shell) != SUCCESS && shell->running)
		{
			sh_free_all(shell);
			return (sh_reset_shell(FAILURE));
		}
	}
	sh_free_all(shell);
	return (sh_reset_shell(SUCCESS));
}
