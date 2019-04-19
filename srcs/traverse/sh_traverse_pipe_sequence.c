/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/19 16:37:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** Case 0:
**		Only one pipe sequence => no pipes mechanism
** Case 1:
**		First command to execute : pipe sequence with only a command
			command
** Case 2:
**		Any middle pipe_sequence
**			pipe_sequence '|' linebreak command
** Case 3:
**		First pipe_sequence, contain last command to execute
**			pipe_sequence '|' linebreak command
*/

static int	sh_traverse_pipe_sequence_1(t_ast_node *node, t_context *context)
{
	int		save_fdout;
	int		res;

	// Case 1 : First pipe_sequence
	save_fdout = context->fd[FD_OUT];
	if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
		return (FAILURE);
	context->fd[FD_OUT] = save_fdout;

	// ft_dprintf(2, "Last command :\n");
	// ft_dprintf(2, "pipe[in] : %d, pipe[out] : %d\n", context->pipe[PIPE_IN],context->pipe[PIPE_OUT]);
	// ft_dprintf(2, "fdin : %d, fdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);

	res = sh_traverse_tools_browse(node, context);
	return (res);
}

static int	sh_traverse_pipe_sequence_2(t_ast_node *node, t_context *context)
{
	int		save_fd;
	int		res;

	// Case 2 : Mid pipe_sequence
	if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
		return (FAILURE);
	save_fd = context->pipe[PIPE_OUT];
	if (pipe(context->pipe))
		return ft_perror(SH_ERR1_INTERN_ERR, "sh_traverse_pipe_sequence_2 : piping");
	context->fd[FD_OUT] = context->pipe[PIPE_IN];

	// ft_dprintf(2, "Mid command :\n");
	// ft_dprintf(2, "pipe[in] : %d, pipe[out] : %d\n", context->pipe[PIPE_IN],context->pipe[PIPE_OUT]);
	// ft_dprintf(2, "fdin : %d, fdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);
	
	res = sh_traverse_tools_browse(node, context);
	context->fd[FD_IN] = context->pipe[PIPE_OUT];
	return (res);
}

static int	sh_traverse_pipe_sequence_3(t_ast_node *node, t_context *context)
{
	int			res;

	// Case 3 : last pipe_sequence (only one command child)
	if (pipe(context->pipe))
		return ft_perror(SH_ERR1_INTERN_ERR, "sh_traverse_pipe_sequence_3: pipe");
	context->fd[FD_OUT] = context->pipe[PIPE_IN];

	// ft_dprintf(2, "First command :\n");
	// ft_dprintf(2, "pipe[in] : %d, pipe[out] : %d\n", context->pipe[PIPE_IN],context->pipe[PIPE_OUT]);
	// ft_dprintf(2, "fdin : %d, fdout : %d\n", context->fd[FD_IN], context->fd[FD_OUT]);

	res = sh_traverse_tools_browse_one_child(node, context);

	context->fd[FD_IN] = context->pipe[PIPE_OUT];
	return (res);
}

int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	t_ast_node		*child;
	int				father;
	
	child = (t_ast_node*)node->children->content;
	father = context->father_id;
	sh_traverse_update_father(node, context);
	if (child->symbol->id == sh_index(COMMAND) && father == sh_index(PIPELINE))
		return (sh_traverse_tools_browse(node, context));
	if (father == sh_index(PIPELINE))
		return (sh_traverse_pipe_sequence_1(node, context));
	else if (child->symbol->id == sh_index(COMMAND))
		return (sh_traverse_pipe_sequence_3(node, context));
	else
		return (sh_traverse_pipe_sequence_2(node, context));
}
