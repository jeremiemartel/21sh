/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 12:37:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
/*
static int	sh_traverse_pipe_sequence_(t_ast_node *node, t_context *context)
{
	(void)node;
	(void)context;
	return (0);
}
*/
int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	t_ast_node *child;

	child = (t_ast_node *)node->children->content;
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		return (SUCCESS);
	else
	{
		if (ft_lstlen(node->children) == 3)
		{
			child->metadata.command_metadata.redirections = NULL;
			context->current_command_node = node;
			return (sh_traverse_tools_browse(node, context));

		}
		else if (child->symbol->id == sh_index(COMMAND))
		{
			child->metadata.command_metadata.redirections = NULL;
			context->current_command_node = node;
			return (sh_traverse_tools_browse(node, context));
		}
		else
			return (sh_traverse_tools_browse(node, context));
	}
}
