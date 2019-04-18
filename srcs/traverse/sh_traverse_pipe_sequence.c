/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/17 23:23:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** Case 1:
**		pipe_sequence    :                             command
**		Only execute children's traverse
** Case 2:
**		                 | pipe_sequence '|' linebreak command
**		Execute children's traverse and reset filedescriptors
*/

// static int		sh_traverse_pipe_sequence_1(t_ast_node *node, t_context *context)
// {

// }

// static int		sh_traverse_pipe_sequence_2(t_ast_node *node, t_context *context)
// {
// }

int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	t_ast_node		*child;
	int				fdin;
	int				fdout;
	int				res = SUCCESS;

	child = (t_ast_node*)node->children->content;
	if (child->symbol->id == sh_index(PIPE_SEQUENCE))
	{
		if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
			return (FAILURE);
	}
	fdin = context->pipe[PIPE_OUT];
	fdout = context->pipe[PIPE_IN];
	pipe(context->pipe);
	if (child->symbol->id == sh_index(COMMAND))
		fdout = 1;
	else
		fdout = context->pipe[PIPE_IN];

	context->fd[FD_IN] = fdin;
	context->fd[FD_OUT] = fdout;
	ft_dprintf(2, "stdin : %d, stdout : %d\n", fdin, fdout);
	ft_dprintf(2, "new pipe : pipe[in] = %d, pipe[out] = %d\n", context->pipe[PIPE_IN], context->pipe[PIPE_OUT]);

	res = sh_traverse_tools_browse(node, context);

	ft_dprintf(2, "stdin : %d, stdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);
	ft_dprintf(2, "new pipe : pipe[in] = %d, pipe[out] = %d\n", context->pipe[PIPE_IN], context->pipe[PIPE_OUT]);
	ft_strtab_put((char**)context->params->tbl);

	if (context->fd[FD_IN] != 0)
		close(fdin);
	if (context->fd[FD_OUT] != 1)
		close (fdout);
	if (context->pipe[PIPE_IN] >= 3)
		close (context->pipe[PIPE_IN]);
	if (context->pipe[PIPE_OUT] >= 3)
		close (context->pipe[PIPE_OUT]);

	return (res);



	// if (child->symbol->id == sh_index(COMMAND))
	// 	return (sh_traverse_pipe_sequence_1(node, context));
	// else if (child->symbol->id == sh_index(PIPE_SEQUENCE))
	// 	return (sh_traverse_pipe_sequence_2(node, context));
	// else
	// 	return (FAILURE);
	return (SUCCESS);
}
