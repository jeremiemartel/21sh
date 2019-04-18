/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/18 17:02:40 by jmartel          ###   ########.fr       */
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
	int				save_fdout;
	int				father;
	child = (t_ast_node*)node->children->content;

	// ft_dprintf(2, "pipe sequence :  \n\t father : %s \n\t children : %s\n", g_grammar[context->father_id].debug, child->symbol->debug);
	// ft_dprintf(2, "\t father id : %d \n\t children id : %d\n", context->father_id, child->symbol->id);

	//	Case 0 : only one command, with no pipe
	father = context->father_id;
	sh_traverse_update_father(node, context);

	if (child->symbol->id == sh_index(COMMAND) && father == sh_index(PIPELINE))
		return (sh_traverse_tools_browse(node, context));

	if (father == sh_index(PIPELINE))
	{
		// Case 1 : First pipe_sequence
		save_fdout = context->fd[FD_OUT];
		if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
			return (FAILURE);
		context->fd[FD_OUT] = save_fdout;

		ft_dprintf(2, "Last command :\n");
		ft_dprintf(2, "pipe[in] : %d, pipe[out] : %d\n", context->pipe[PIPE_IN],context->pipe[PIPE_OUT]);
		ft_dprintf(2, "fdin : %d, fdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);

		if (sh_traverse_tools_browse(node, context) == FAILURE)
			return (FAILURE);
		close(context->pipe[PIPE_OUT]);
	}
	else if (child->symbol->id == sh_index(COMMAND))
	{
		// Case 3 : last pipe_sequence (only one command child)
		pipe(context->pipe);
		context->fd[FD_OUT] = context->pipe[PIPE_IN];

		ft_dprintf(2, "First command :\n");
		ft_dprintf(2, "pipe[in] : %d, pipe[out] : %d\n", context->pipe[PIPE_IN],context->pipe[PIPE_OUT]);
		ft_dprintf(2, "fdin : %d, fdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);

		if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
			return (FAILURE);
		close(context->pipe[PIPE_IN]);
		context->fd[FD_IN] = context->pipe[PIPE_OUT];
		return (SUCCESS);
	}
	else
	{
		// Case 2 : Mid pipe_sequence
		if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
			return (FAILURE);
		save_fdout = context->pipe[PIPE_OUT];
		pipe(context->pipe);
		context->fd[FD_OUT] = context->pipe[PIPE_IN];

		ft_dprintf(2, "Mid command :\n");
		ft_dprintf(2, "pipe[in] : %d, pipe[out] : %d\n", context->pipe[PIPE_IN],context->pipe[PIPE_OUT]);
		ft_dprintf(2, "fdin : %d, fdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);
		
		if (sh_traverse_tools_browse(node, context) == FAILURE)
			return (FAILURE);
		close(save_fdout);
		close(context->pipe[PIPE_IN]);
		context->fd[FD_IN] = context->pipe[PIPE_OUT];
		return (SUCCESS);
	}
	return (SUCCESS);
}
