/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/16 17:52:38 by jmartel          ###   ########.fr       */
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

static int		sh_traverse_pipe_sequence_1(t_ast_node *node, t_context *context)
{
	ft_putstrn("Entering pipesequence 1");
	return (sh_traverse_tools_browse(node, context));
}

static int		sh_traverse_pipe_sequence_2(t_ast_node *node, t_context *context)
{
	int			save_std[3];
	int			pipe_fd[2];
	t_list		*head = node->children;
	t_ast_node	*child = (t_ast_node*)head->content;

	// Saving in and output locally
	save_std[0] = dup(context->std[0]);
	save_std[1] = dup(context->std[1]);
	// Piping input to pipe enter
	pipe(pipe_fd);
	dup2(pipe_fd[PIPE_IN], context->std[1]);
	// Calling first children
	if (g_grammar[child->symbol->id].traverse(child, context) == FAILURE)
		return (FAILURE);
	head = head->next;
	child = (t_ast_node*)head->content;
	//Executing waiting command
	sh_traverse_tools_flush(context);
	dup2(pipe_fd[PIPE_OUT], context->std[0]);
	// Reseting output
	close(context->std[1]);
	dup2(context->std[1], save_std[1]);
	// Executing 2 last sons
	while (head)
	{
		child = (t_ast_node*)head->content;
		if (g_grammar[child->symbol->id].traverse(child, context) == FAILURE)
			return (FAILURE);
		head = head->next;
	}
	// Reseting std
	close(context->std[0]);
	dup2(context->std[0], save_std[0]);
	return (SUCCESS);
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
