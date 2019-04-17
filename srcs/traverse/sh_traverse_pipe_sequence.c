/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/17 11:28:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

# define PIPE_IN	1
# define PIPE_OUT	0

/*
** Case 1:
**		pipe_sequence    :                             command
**		Only execute children's traverse
** Case 2:
**		                 | pipe_sequence '|' linebreak command
**		Execute children's traverse and reset filedescriptors
*/

#define FD_IN		0
#define FD_OUT		1
#define FD_ERR		2

#define PIPE_IN		1
#define PIPE_OUT	0

static int		sh_traverse_pipe_sequence_prefork_fd(t_ast_node *node, t_context *context)
{
	context->fd[FD_IN] = context->pipe[PIPE_OUT];
	pipe(context->pipe);
	context->fd[FD_OUT] = context->pipe[PIPE_IN]; // Cas a regler pour le dernier pipe
	return (SUCCESS);
	(void)node;
	(void)(context);
}

static int		sh_traverse_pipe_sequence_postfork_fd(t_ast_node *node, t_context *context)
{
	if (context->fd[FD_IN] != 0)
		close(context->fd[FD_IN]);
	if (context->fd[FD_OUT] != 1)
		close(context->fd[FD_OUT]);
	return (SUCCESS);
	(void)node;
	(void)(context);
}
/*
static int		sh_traverse_pipe_sequence_fork(t_ast_node *node, t_context *context)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
	{
		if (dup2(context->fd[FD_IN], 0) == -1)
			return (FAILURE);
		if (dup2(context->fd[FD_OUT], 1) == -1)
			return (FAILURE);
		execve(context->params->tbl[0], context->params->tbl, context->env->tbl);
		return (ft_perror("Command not found", context->params->tbl[0]));
	}
}
*/
static int		sh_traverse_pipe_sequence_1(t_ast_node *node, t_context *context)
{
	sh_traverse_pipe_sequence_prefork_fd(node, context);
	return (sh_traverse_tools_browse(node, context));
}

static int		sh_traverse_pipe_sequence_2(t_ast_node *node, t_context *context)
{
	if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
		return (FAILURE);
	if (sh_traverse_pipe_sequence_prefork_fd(node, context) == FAILURE)
		return (FAILURE);
	if (sh_traverse_tools_browse(node, context) == FAILURE)
		return (FAILURE);
	return (sh_traverse_pipe_sequence_postfork_fd(node, context));
}

int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	t_ast_node		*child;

	child = (t_ast_node*)node->children->content;
	if (child->symbol->id == sh_index(COMMAND))
		return (sh_traverse_pipe_sequence_1(node, context));
	else if (child->symbol->id == sh_index(PIPE_SEQUENCE))
		return (sh_traverse_pipe_sequence_2(node, context));
	else
		return (FAILURE);
	return (SUCCESS);
}
