/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 16:46:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_append_to_historic(t_shell *shell, char *command)
{
	int		fd;
	char	*str;

	if (!ft_strcmp(command, "")
		|| (shell->historic.commands
			&& !ft_strcmp((char *)shell->historic.commands->content, command)))
		return (SUCCESS);
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

int		sh_process_command(t_shell *shell, char *command)
{
	t_list *tokens;

	if (lexer(command, &tokens, shell->env) != SUCCESS)
		return (FAILURE);
	if (sh_parser(tokens, shell))
	   	return (FAILURE);
	return (sh_process_traverse(shell));
}

/*
int		sh_process_new_partial_command(char **full_command, t_command_line *command_line)
{
	if (!*full_command && !(*full_command = ft_strdup(command_line->dy_str->str)))
		return (FAILURE);
	else
		ft_
	return (SUCCESS);
}
*/
int		sh_await_command(t_shell *shell)
{
//	char	*full_command;

//	full_command = NULL;
//	g_glob.command_line.state = DEFAULT;
	if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
/*
	while (g_glob.command_line.state != DEFAULT)
	{
		if (sh_get_command(shell, &g_glob.command_line) != SUCCESS)
			return (FAILURE);
		if (sh_process_add(&full_command, &g_glob.command_line) != SUCCESS)
			return (FAILURE);
	}
*/
	if (sh_append_to_historic(shell, g_glob.command_line.dy_str->str) != SUCCESS)
		return (FAILURE);
	return (sh_process_command(shell, g_glob.command_line.dy_str->str));
}

int		sh_process_canonical_mode(t_shell *shell) //to change
{
	int		ret;
	char	*str;
	char	*command;

	if (!(command = ft_strnew(0)))
		return (1);
	while (get_next_line(0, &str) > 0)
	{
		if (!(command = ft_strjoin_free(command, str, 1))) //to protect omg
		{
			free(str);
			return (1);
		}
		free(str);
	}
	free(str);
	ret = (sh_process_command(shell, command));
	return (ret);
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
