/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tok_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:14:10 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/16 17:25:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_tok_pipe(t_ast_node *node, t_context *context)
{
	return (sh_traverse_tools_browse(node, context));
/*	int		pipe_fd[2];
	int		res;

	ft_putstrn("Entering pipe token");
	ft_strtab_put((char **)context->params->tbl);
	
	context->std[0] = dup(0);
	context->std[1] = dup(1);
	if (pipe(pipe_fd) != 0)
		return (FAILURE);
	if (dup2(pipe_fd[PIPE_IN], 1) == -1)
		return (FAILURE);
	res = sh_traverse_tools_flush(context);
	close(pipe_fd[PIPE_IN]);
	dup2(context->std[1], 1);
	if (dup2(pipe_fd[PIPE_OUT], 0) == -1)
		return (FAILURE);
	return (SUCCESS);
	(void)node;
	*/
}

/*
int		sh_traverse_tok_pipe(t_ast_node *node, t_context *context)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		res;

	if (pipe(pipe_fd) != 0)
		return (FAILURE);
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
	{
		if (dup2(pipe_fd[PIPE_IN], 1) == -1)
			return (FAILURE);
		close(pipe_fd[PIPE_OUT]);
		execve(context->params->tbl[0], context->params->tbl[1], context->env->tbl);
		ft_perror("Command not found", "traverse_tok_pipe");
		return (FAILURE);
	}
	wait(&res);
	if (dup2(pipe_fd[PIPE_OUT], 1) == -1)
		return (FAILURE);
	if (res == FAILURE)
		return (res);
	return (SUCCESS);
}
*/
/*
int		sh_traverse_tok_pipe(t_ast_node *node, t_context *context)
{
	int		pipe_fd[2];
	int		ret;
	
	if (pipe(pipe_fd) == -1)
		return (FAILURE);
	if (dup2(pipe_fd[PIPE_IN], 1) == -1)
		return (FAILURE);
	if (dup2(pipe_fd[PIPE_OUT], 0) == -1)
		return (FAILURE);
	ret = sh_traverse_tools_flush(context);

	return (SUCCESS);
	(void)node;
	(void)context;
	// return (sh_traverse_tools_browse(node, context));
}
*/