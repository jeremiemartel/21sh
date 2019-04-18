/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/18 12:36:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t g_parent = 0;

void	transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	return (exit(sh_reset_shell(0)));
}

void	transmit_sig(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	get_down_from_command(&g_glob.command_line);
	g_glob.cursor = 0;
	g_glob.command_line.dy_str->current_size = 0;
	g_glob.command_line.current_index = 0;
	ft_bzero(g_glob.command_line.dy_str->str, g_glob.command_line.dy_str->max_size);
	g_glob.command_line.nb_chars = 0;
	render_command_line(g_glob.command_line.dy_str, 0);
}

int		process_execute_pipes(t_context *context)
{
	// if (context->fd[FD_IN] != 0)
		if (dup2(context->fd[FD_IN], 0) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_pipes 1"));
	// if (context->fd[FD_OUT] != 1)
		if (dup2(context->fd[FD_OUT], 1) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_pipes 2"));
		if (context->pipe[PIPE_OUT] != 1)
			close (context->pipe[PIPE_OUT]);
	// if (context->fd[FD_ERR] != 2)
	// 	if (dup2(context->fd[FD_ERR], 2) == -1)
	// 		return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_pipes 3"));

	return (SUCCESS);
}

int		process_execute(char *path, t_context *context)
{
	if (check_execute(path, context->params->tbl[0]))
		return (1);
	if (sh_reset_shell(0) == -1)
		return (1);
	if ((g_parent = fork()) == -1)
		return (1);
	if (g_parent == 0)
	{
		process_execute_pipes(context);
		if (execve(path, (char **)context->params->tbl,
				(char **)context->env->tbl) == -1)
		{
	//		free_all(shell);
	//		exit(1);
			exit(ft_perror(SH_ERR1_CMD_NOT_FOUND, *context->params->tbl));
		}
	}
	else
	{
		wait(NULL);
		g_parent = 0;
		if (tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (ft_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
	}
	return (0);
}
