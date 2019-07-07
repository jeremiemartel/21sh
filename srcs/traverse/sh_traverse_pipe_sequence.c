/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/03 22:54:22 by ldedier          ###   ########.fr       */
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
	redir.fd = fds[PIPE_IN];
	redir.other_pipe_fd = fds[PIPE_OUT];
	if (sh_add_redirection(redir,
		&from->metadata.command_metadata.redirections))
		return (FAILURE);
	redir.type = INPUT;
	redir.redirected_fd = 0;
	redir.fd = fds[PIPE_OUT];
	redir.other_pipe_fd = fds[PIPE_IN];
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

	ptr = (t_list *)node->children;
	from = NULL;
	while (ptr != NULL)
	{
		to = ((t_ast_node *)(ptr->content))->children->content;
		if (from != NULL && sh_add_pipe_redirections(from, to))
			return (FAILURE);
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

	sh_init_command_redirections_list(node);
	if (sh_process_pipe_redirections(node))
		return (FAILURE);
	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		from = (t_ast_node *)(ptr->content);
		simple_command_node = from->children->content;
		context->current_command_node = simple_command_node;
		if (g_grammar[from->symbol->id].traverse(from, context) == FAILURE)
			return (FAILURE);
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
	return (SUCCESS);
}

void			sh_process_execute_close_pipes_list(t_list *contexts)
{
	t_list		*ptr;
	t_context	*context;

	ptr = contexts;
	while (ptr != NULL)
	{
		context = (t_context *)ptr->content;	
		sh_process_execute_close_pipes(context);
		ptr = ptr->next;
	}
}

void			sh_process_execute_close_pipes_pid(t_list *contexts, pid_t pid)
{
	t_list		*ptr;
	t_context	*context;

	ptr = contexts;
	while (ptr != NULL)
	{
		context = (t_context *)ptr->content;
		if (context->pid == pid)
		{
			ft_printf("on close les fd de  %s\n", context->path);
			sh_process_execute_close_pipes(context);
			return ;
		}
		ptr = ptr->next;
	}
}

int				process_pipe_sequence_execute(t_ast_node *node,
					t_context *context, t_list **contexts)
{
	int			res;
	t_context	*context_iter;
	t_list		*ptr;

	(void)node;
	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes_list(*contexts);
		return (FAILURE);
	}
	ptr = *contexts;
	while (ptr != NULL)
	{
		context_iter = (t_context *)ptr->content;
		if ((context_iter->pid = fork()) == -1)
			return (FAILURE);
		if (context_iter->pid == 0)
			sh_execute_child(context_iter, *contexts);
		else
		{
			g_parent = context_iter->pid;
			ptr =  ptr->next;
		}
	}
	sh_process_execute_close_pipes_list(*contexts);
	pid_t wpid;
	while ((wpid = wait(&res)) > 0)
	{
		ft_printf("on a catch le pid: %d\n", wpid);
		if (wpid == g_parent)
		{
	//		sh_process_execute_close_pipes_pid(*contexts, wpid);
		//	break ;
		}
		else
		{
	//		sh_process_execute_close_pipes_pid(*contexts, wpid);
		}
	}
	sh_env_vars_update_question_mark(context, res);
	g_parent = 0;
//	sh_process_execute_close_pipes_list(*contexts);
	if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	return (SUCCESS);
}

int				sh_traverse_pipe_sequence_execute(t_ast_node *node,
		t_context *context)
{
	int ret;

	if (ft_lstlen(node->children) == 1)
	{
		context->current_pipe_sequence_node = NULL;
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		context->current_pipe_sequence_node = node;
		node->metadata.pipe_metadata.contexts = NULL;
		ret = sh_traverse_tools_browse(node, context); // fill the list of contexts
		return (process_pipe_sequence_execute(node, context, &node->metadata.
					pipe_metadata.contexts));
	}
}

int				sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		return (sh_traverse_pipe_sequences_redirections(node, context));
	else if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
		return (sh_traverse_pipe_sequence_execute(node, context));
	else
		return (sh_traverse_tools_browse(node, context));
}
