/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 15:58:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

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
				ft_dprintf(2, "\t%d became %d\n",
					redir->fd, redir->redirected_fd);
			if (dup2(redir->fd, redir->redirected_fd) == -1)
				return (sh_perror(SH_ERR1_INTERN_ERR,
					"process_exec_dup_pipes 2"));
		}
		else if (redir->fd == -1)
		{
			if (sh_verbose_pipe())
				ft_dprintf(2, "\tclosing %d\n", redir->redirected_fd);
			close(redir->redirected_fd);
		}
		else if (redir->fd == -2)
		{
			redir->fd = dup(redir->redirected_fd);
			dup2(redir->fd, redir->redirected_fd);
			ft_dprintf(2, "\t%d became %d\n", redir->fd, redir->redirected_fd);
		}
		head = head->next;
	}
	return (SUCCESS);
}

int			sh_process_execute_close_pipes(t_context *context)
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

int			sh_process_execute(t_context *context)
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
		sh_perror_err(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
		exit(FAILURE);
	}
	else
	{
		wait(&res);
		sh_env_vars_update_question_mark(context, res);
		g_parent = 0;
		sh_process_execute_close_pipes(context);
		if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (sh_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
	}
	return (SUCCESS);
}
