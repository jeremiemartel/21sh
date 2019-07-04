/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:26:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/04 21:18:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_process_execute_dup_pipes(t_redirection *redir)
{
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
	return (SUCCESS);
}

int			sh_process_execute_dup_pipes(t_context *context)
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
		if (sh_process_process_execute_dup_pipes(redir))
			return (FAILURE);
		head = head->next;
	}
	return (SUCCESS);
}

static void	sh_process_process_execute_close_pipes(t_redirection *redir)
{
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
}

int			sh_process_execute_close_pipes(t_context *context)
{
	t_list			*head;
	t_redirection	*redir;

	if (!context->redirections)
		return (SUCCESS);
	if (sh_verbose_pipe() && context->params->tbl[0] != NULL)
		ft_dprintf(2, "closing for %s:\n", context->params->tbl[0]);
	head = *(context->redirections);
	while (head)
	{
		redir = (t_redirection*)head->content;
		sh_process_process_execute_close_pipes(redir);
		head = head->next;
	}
	return (SUCCESS);
}
