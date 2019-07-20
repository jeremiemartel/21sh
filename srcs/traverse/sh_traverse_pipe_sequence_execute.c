/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence_execute.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/20 08:05:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_traverse_pipe_sequence_execute(t_ast_node *node,
		t_context *context)
{
	int ret;

	node->metadata.pipe_metadata.contexts = NULL;
	if (ft_lstlen(node->children) == 1)
	{
		context->current_pipe_sequence_node = NULL;
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		context->current_pipe_sequence_node = node;
		if ((ret = sh_traverse_tools_browse(node, context)) != SUCCESS)
			return (ret);
		return (sh_execute_pipe_sequence(context,
			node->metadata.pipe_metadata.contexts));
	}
}
