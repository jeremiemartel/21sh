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

int		sh_append_to_historic(t_shell *shell, char *command)
{
	int fd;
	
	char	*str;

	if (!(str = ft_strdup(command)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_append_to_historic"));
	if (ft_add_to_dlist_ptr(&shell->historic.commands, str, sizeof(str)))
	{
		free(str);
		return (ft_perror(SH_ERR1_MALLOC, "sh_append_to_historic"));
	}
	if ((fd = open(HISTORIC_FILE, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
		return (ft_perror(SH_ERR1_HISTORIC, "sh_append_to_historic"));
	ft_dprintf(fd, "%s\n", command);
	shell->historic.head_start.next = shell->historic.commands;
	close(fd);
	return (SUCCESS);
}

int		sh_await_command(t_shell *shell)
{
	t_list *tokens;

	if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	if (ft_strcmp(g_glob.command_line.dy_str->str, "")
		&& (sh_append_to_historic(shell,
			g_glob.command_line.dy_str->str) != SUCCESS))
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
