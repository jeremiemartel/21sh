/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 17:14:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_add_pipe_redirections(t_ast_node *from, t_ast_node *to)
{
	int				fds[2];
	t_redirection	redir;

	if (pipe(fds))
		return (sh_perror(SH_ERR1_PIPE, "add_pipe_redirections"));
	redir.type = OUTPUT;
	redir.redirected_fd = 1;
	redir.closed = 0;
	redir.fd = fds[PIPE_IN];
	if (sh_add_redirection(redir,
		&from->metadata.command_metadata.redirections))
		return (FAILURE);
	redir.closed = 0;
	redir.type = INPUT;
	redir.redirected_fd = 0;
	redir.fd = fds[PIPE_OUT];
	if (sh_add_redirection(redir, &to->metadata.command_metadata.redirections))
		return (FAILURE);
	return (SUCCESS);
}

static void		sh_init_command_redirections_list(t_ast_node *node)
{
	t_list		*ptr;
	t_ast_node	*child;

	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		child = ptr->content;
		((t_ast_node *)(child->children->content))
			->metadata.command_metadata.redirections = NULL;
		((t_ast_node *)(child->children->content))
			->metadata.command_metadata.should_exec = 1;
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
}

static int		sh_process_pipe_redirections(t_ast_node *node)
{
	t_list		*ptr;
	t_ast_node	*from;
	t_ast_node	*to;
	int			ret;

	ret = 0;
	ptr = (t_list *)node->children;
	from = NULL;
	while (ptr != NULL)
	{
		to = ((t_ast_node *)(ptr->content))->children->content;
		if (from != NULL && (ret = sh_add_pipe_redirections(from, to)))
			return (ret);
		if ((ptr = ptr->next))
			ptr = ptr->next;
		from = to;
	}
	return (SUCCESS);
}

static int		sh_traverse_pipe_sequences_redirections(t_ast_node *node,
		t_context *context)
{
	t_ast_node	*from;
	t_ast_node	*simple_command_node;
	t_list		*ptr;
	int			ret;

	sh_init_command_redirections_list(node);
	if ((ret = sh_process_pipe_redirections(node)))
		return (ret);
	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		from = (t_ast_node *)(ptr->content);
		simple_command_node = from->children->content;
		context->current_command_node = simple_command_node;
		if ((ret = g_grammar[from->symbol->id].traverse(from, context)))
			return (ret);
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
	return (SUCCESS);
}

int				sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	int		ret;

	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE"PIPE_SEQUENCE : %s : start\n"EOC,
		t_phase_name(context->phase));
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		ret = sh_traverse_pipe_sequences_redirections(node, context);
	else if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
		ret = sh_traverse_pipe_sequence_execute(node, context);
	else
		ret = sh_traverse_tools_browse(node, context);
	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE"PIPE_SEQUENCE : %s : returned value : %s\n"EOC,
		t_phase_name(context->phase), ret_to_str(ret));
	return (ret);
}
