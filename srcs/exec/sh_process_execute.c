/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/27 19:04:07 by ldedier          ###   ########.fr       */
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
	if (g_glob.command_line.dy_str)
	{
		get_down_from_command(&g_glob.command_line);
		g_glob.cursor = 0;
		g_glob.command_line.dy_str->current_size = 0;
		g_glob.command_line.current_index = 0;
		ft_bzero(g_glob.command_line.dy_str->str, g_glob.command_line.dy_str->max_size);
		g_glob.command_line.nb_chars = 0;
		render_command_line(&g_glob.command_line, 0, 1);
	}
}

static int	sh_process_execute_dup_pipes(t_context *context)
{
	t_list			*head;
	t_redirection	*redir;

	if (!context->redirections)
		return (SUCCESS);
	if (sh_verbose_pipe())
		ft_dprintf(2, "Redirections for %s:\n", context->params->tbl[0]);
	head = *(context->redirections);
	while (head)
	{
		redir = (t_redirection*)head->content;
		if (redir->fd >= 0)
		{
			if (sh_verbose_pipe())
				ft_dprintf(2, "\t%d became %d\n", redir->fd, redir->redirected_fd);
			if (dup2(redir->fd, redir->redirected_fd) == -1)
				return (ft_perror(SH_ERR1_INTERN_ERR, "process_exec_dup_pipes 2"));
		}
		else if (redir->fd == -1)
		{
			ft_dprintf(2, "\tclosing %d\n", redir->redirected_fd);
			close(redir->redirected_fd);
		}
		else if (redir->fd == -2)
		{
//			redir->fd = dup(redir->redirected_fd);
//			dup2(redir->fd, redir->redirected_fd);
//			ft_dprintf(2, "\t%d became %d\n", redir->fd, redir->redirected_fd);
			ft_dprintf(2, "TAMER\n");
		}
		head = head->next;
	}
	return (SUCCESS);
}

static int	sh_process_execute_close_pipes(t_context *context)
{
	t_list			*head;
	t_redirection	*redir;

	if (!context->redirections)
		return (SUCCESS);
	if (sh_verbose_pipe())
		ft_dprintf(2, "closing for %s:\n", context->params->tbl[0]);
	head = *(context->redirections);
	while (head)
	{
		redir = (t_redirection*)head->content;
		if (redir->fd > 2)
		{
			if (sh_verbose_pipe())
				ft_dprintf(2, "\tclosing %d\n", redir->fd);
			close(redir->fd);
		}
		else if (redir->fd >= 0)
		{
			if (redir->fd != redir->redirected_fd)
			{
				if (sh_verbose_pipe())
					ft_dprintf(2, "\tclosing %d\n", redir->redirected_fd);
				close(redir->redirected_fd);
			}
		}
		else if (redir->fd == -2)
		{
			if (sh_verbose_pipe())
				ft_dprintf(2, "\tclosing %d\n", redir->redirected_fd);
			close(redir->redirected_fd);
		}
		head = head->next;
	}
	return (SUCCESS);
}

int		sh_process_execute_builtin_fill_fd(t_context *context)
{
	t_list			*head;
	t_redirection	*redir;

	if (!context->redirections)
		return (SUCCESS);
	context->fd[0] = 0;
	context->fd[1] = 1;
	context->fd[2] = 2;
	head = *(context->redirections);
	while (head)
	{
		redir = head->content;
		if (redir->type == OUTPUT && redir->redirected_fd >= 0
				&& redir->redirected_fd <= 2)
			context->fd[redir->redirected_fd] = redir->fd;
		head = head->next;
	}
	if (sh_verbose_pipe())
	{
		ft_dprintf(2, "process_Execute_dup_pipes\n");
		ft_dprintf(2, "\tfdin  : %d\n", context->fd[FD_IN]);
		ft_dprintf(2, "\tfdout : %d\n", context->fd[FD_OUT]);
		ft_dprintf(2, "\tfderr : %d\n", context->fd[FD_ERR]);
	}
	return (SUCCESS);
}

int		sh_process_execute_builtin(t_context *context)
{
	int		res;

	sh_process_execute_builtin_fill_fd(context);
	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	res = context->builtin(context);
	sh_env_vars_update_question_mark(context, res);
	if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
		return (ft_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	sh_process_execute_close_pipes(context);
	return (SUCCESS);
}

int		sh_process_execute(t_context *context)
{
	int		res;

	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	if ((g_parent = fork()) == -1)
		return (FAILURE);
	if (g_parent == 0)
	{
		sh_process_execute_dup_pipes(context);
		execve(context->path, (char **)context->params->tbl, (char **)context->env->tbl);
		sh_process_execute_close_pipes(context);
		ft_perror(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
		exit(FAILURE);
	}
	else
	{
		wait(&res);
		sh_env_vars_update_question_mark(context, res);
		g_parent = 0;
		sh_process_execute_close_pipes(context);
		if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (ft_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
	}
	return (SUCCESS);
}
