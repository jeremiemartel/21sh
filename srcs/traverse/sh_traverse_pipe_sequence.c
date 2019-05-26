/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 16:04:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int sh_add_pipe_redirections(t_ast_node *from, t_ast_node *to)
{
	int fds[2];

	if (pipe(fds))
		return (ft_perror(SH_ERR1_PIPE, "add_pipe_redirections"));
	if (sh_add_redirection(OUTPUT, 1, fds[1],
			&from->metadata.command_metadata.redirections))
		return (FAILURE);
	if (sh_add_redirection(INPUT, 0, fds[0],
			&to->metadata.command_metadata.redirections))
		return (FAILURE);
	return (SUCCESS);
}

static void sh_init_command_redirections_list(t_ast_node *node)
{
	t_list *ptr;
	t_ast_node	*child;

	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		child = ptr->content;
		child->metadata.command_metadata.redirections = NULL;
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
}

static int	sh_process_pipe_redirections(t_ast_node *node)
{
	t_list		*ptr;
	t_ast_node	*from;
	t_ast_node	*to;

	ptr = (t_list *)node->children;
	from = NULL;
	while (ptr != NULL)
	{
		to = ptr->content;
		if (from != NULL && sh_add_pipe_redirections(from, to))
			return (FAILURE);
		if ((ptr = ptr->next))
			ptr = ptr->next;
		from = to;
	}
	return (SUCCESS);
}

static int sh_traverse_pipe_sequences_redirections(t_ast_node *node,
			t_context *context)
{
	t_ast_node	*from;
	t_list		*ptr;

	sh_init_command_redirections_list(node);
	if (sh_process_pipe_redirections(node))
		return (FAILURE);
	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		from = ptr->content;
		context->current_command_node = from;
		if (g_grammar[from->symbol->id].traverse(from, context) == FAILURE)
			return (FAILURE);
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
	return (SUCCESS);
}

int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		return (sh_traverse_pipe_sequences_redirections(node, context));
	else
		return (sh_traverse_tools_browse(node, context));
}
