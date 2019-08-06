/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/30 19:45:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_traverse_and_or_call_sons_exec(t_ast_node *node,
		int *prev_symbol, t_context *context)
{
	t_ast_node	*child;
	int			ret;

	if (*prev_symbol == -1)
		;
	else if (*prev_symbol == sh_index(LEX_TOK_AND_IF)
		&& context->shell->ret_value)
		return (SUCCESS);
	else if (*prev_symbol == sh_index(LEX_TOK_OR_IF)
		&& !context->shell->ret_value)
		return (SUCCESS);
	child = (t_ast_node*)(node->children->content);
	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (ret == FAILURE || ret == STOP_CMD_LINE)
		return (ret);
	if (!context->shell->running)
		return (ret);
	return (SUCCESS);
}

static int		sh_traverse_and_or_call_sons(
	t_ast_node *node, t_context *context, t_phase phase)
{
	int			ret;

	context->phase = phase;
	ret = g_grammar[node->symbol->id].traverse(node, context);
	if (!context->shell->running)
		return (ret);
	if (ret)
	{
		if (sh_env_update_question_mark(context->shell) == FAILURE)
			return (FAILURE);
		return (ret);
	}
	if (ret == ERROR)
		return (ERROR);
	return (KEEP_READ);
}

static int		sh_traverse_and_or_process_phase(
	t_context *context, t_phase *phase, int prev_symbol, t_list *ptr)
{
	int			ret;
	t_ast_node	*child;

	child = (t_ast_node*)ptr->content;
	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE"AND_OR : %s : start\n"EOC, t_phase_name(*phase));
	context->phase = *phase;
	if (*phase == E_TRAVERSE_PHASE_EXECUTE)
		ret = sh_traverse_and_or_call_sons_exec(child, &prev_symbol, context);
	else
		ret = sh_traverse_and_or_call_sons(child, context, *phase);
	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE"AND_OR : %s : returned value : %s\n"EOC,
		t_phase_name(*phase), ret_to_str(ret));
	(*phase)++;
	if (ret == KEEP_READ || ret == STOP_CMD_LINE || ret == FAILURE)
		return (ret);
	if (ret == ERROR)
	{
		if (*phase - 1 == E_TRAVERSE_PHASE_EXPANSIONS)
			return (SUCCESS);
		set_failed_command(context);
		return (KEEP_READ);
	}
	return (KEEP_READ);
}

int				sh_traverse_and_or_launch_phase(
	t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	int			ret;
	t_phase		phase;
	int			prev_symbol;

	ptr = node->children;
	prev_symbol = -1;
	while (ptr != NULL && context->shell->running)
	{
		phase = E_TRAVERSE_PHASE_EXPANSIONS;
		while (phase <= E_TRAVERSE_PHASE_EXECUTE)
		{
			if ((ret = sh_traverse_and_or_process_phase(
				context, &phase, prev_symbol, ptr)) == KEEP_READ)
				continue ;
			return (ret);
		}
		if ((ptr = (ptr)->next))
		{
			prev_symbol = ((t_ast_node*)ptr->content)->symbol->id;
			ptr = (ptr)->next;
		}
	}
	return (SUCCESS);
}

int				sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE"%s : %s : start\n"EOC,
			node->symbol->debug, t_phase_name(context->phase));
		return (sh_traverse_tools_browse(node, context));
	}
	else if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
		return (sh_traverse_and_or_launch_phase(node, context));
	else
		return (sh_traverse_tools_browse(node, context));
}
