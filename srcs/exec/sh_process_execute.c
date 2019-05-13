/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/13 11:47:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t g_parent = 0;

int		sh_env_update_question_mark(t_context *context, int res)
{
	char	*str;

	if (VERBOSE)
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> "COLOR_END);
	if (!(str = ft_itoa(res)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	if (VERBOSE)
		ft_dprintf(2, COLOR_CYAN"%s\n"COLOR_END, str);
	res = sh_add_to_env(context->env, "?", str);
	free(str);
	return (res);
}

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
	render_command_line(&g_glob.command_line, 0);
}

static int	sh_process_execute_dup_pipes(t_context *context)
{
	if (VERBOSE)
	{
		ft_dprintf(2, "process_Execute_dup_pipes\n");
		ft_dprintf(2, "\tfdin  : %d\n", context->fd[FD_IN]);
		ft_dprintf(2, "\tfdout : %d\n", context->fd[FD_OUT]);
		ft_dprintf(2, "\tfderr : %d\n", context->fd[FD_ERR]);
	}
	if (context->fd[FD_IN] != 0)
		if ((dup2(context->fd[FD_IN], 0)) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_dup_pipes 1"));
	if (context->fd[FD_OUT] != 1)
		if (dup2(context->fd[FD_OUT], 1) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_dup_pipes 2"));
	return (SUCCESS);
}

static int	sh_process_execute_close_pipes(t_context *context)
{
	if (context->fd[FD_IN] != 0)
		if (close(context->fd[FD_IN]) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_close_pipes 0"));
	if (context->fd[FD_OUT] != 1)
		if (close(context->fd[FD_OUT]) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_close_pipes 1"));
	if (context->fd[FD_ERR] != 2)
		if (close(context->fd[FD_ERR]) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_close_pipes 2"));
	return (SUCCESS);
}

int		sh_process_execute_builtin(t_context *context)
{
	int		res;

	if (sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	res = context->builtin(context);
	sh_env_update_question_mark(context, res);
	// ft_dprintf(2, COLOR_RED"res : %d\n"COLOR_END, res);
	if (tcsetattr(0, TCSADRAIN, context->term) == -1)
		return (ft_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	sh_process_execute_close_pipes(context);
	return (SUCCESS);
}

int		sh_process_execute(t_context *context)
{
	int		res;

	if (sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	if ((g_parent = fork()) == -1)
		return (FAILURE);
	if (g_parent == 0)
	{
		sh_process_execute_dup_pipes(context);
		if (context->builtin)
			exit(context->builtin(context));
		execve(context->params->tbl[0], (char **)context->params->tbl, (char **)context->env->tbl);
		sh_process_execute_close_pipes(context);
		exit(FAILURE);
	}
	else
	{
		wait(&res);
		sh_env_update_question_mark(context, res);
		// ft_dprintf(2, COLOR_RED"res : %d\n"COLOR_END, res);
		g_parent = 0;
		sh_process_execute_close_pipes(context);
		if (tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (ft_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
	}
	return (SUCCESS);
}
