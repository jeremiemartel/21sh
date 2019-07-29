/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 03:11:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_traverse_and_or_execute_process(t_ast_node *node,
		int *prev_symbol, t_context *context)
{
	t_ast_node	*child;
	int			ret;

	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE "AND_OR : %s : prev_symbol : %d || AND_IF : %d || OR_IF : %d\n"EOC, t_phase_name(context->phase), *prev_symbol, sh_index(LEX_TOK_AND_IF), sh_index(LEX_TOK_OR_IF));
	if (*prev_symbol == -1)
	{
		;
	}
	else if (*prev_symbol == sh_index(LEX_TOK_AND_IF) && context->shell->ret_value)
	{
		if (sh_verbose_traverse())
		{
			ft_dprintf(2, BLUE "AND_OR : %s : prev_symbol : &&\n"EOC, t_phase_name(context->phase));	
			ft_dprintf(2, BLUE "AND_OR : %s : ret_value : %d\n"EOC, t_phase_name(context->phase), context->shell->ret_value);
		}
		return (SUCCESS);
	}
	else if (*prev_symbol == sh_index(LEX_TOK_OR_IF) && !context->shell->ret_value)
	{
		if (sh_verbose_traverse())
		{
			ft_dprintf(2, BLUE "AND_OR : %s : prev_symbol : &&\n"EOC, t_phase_name(context->phase));
			ft_dprintf(2, BLUE "AND_OR : %s : ret_value : %d\n"EOC, context->shell->ret_value);
		}
		return (SUCCESS);

	}
	child = (t_ast_node*)(node->children->content);
	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (ret == FAILURE || ret == STOP_CMD_LINE)
		return (ret);
	if (!context->shell->running)
		return (ret);
	return (KEEP_READ);
}

static int		sh_traverse_and_or_execute(t_ast_node *node, t_context *context, int *prev_symbol)
{
	int			ret;

	if ((ret = sh_traverse_and_or_execute_process(node,
		prev_symbol, context)) != KEEP_READ)
		return (ret);
	return (SUCCESS);
}

int				sh_traverse_and_or_process_phase(t_ast_node *node, t_context *context, t_phase phase)
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

int				sh_traverse_and_or_launch_phase(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;
	t_phase		phase;
	int			prev_symbol;

	ptr = node->children;
	prev_symbol = -1;
	while (ptr != NULL && context->shell->running)
	{
		child = (t_ast_node*)ptr->content;
		phase = E_TRAVERSE_PHASE_EXPANSIONS;
		while (phase <= E_TRAVERSE_PHASE_EXECUTE)
		{
			if (sh_verbose_traverse())
				ft_dprintf(2, BLUE
				"AND_OR : %s : start\n"EOC, t_phase_name(phase));
			context->phase = phase;
			if (phase == E_TRAVERSE_PHASE_EXECUTE)
				ret = sh_traverse_and_or_execute(child, context, &prev_symbol);
			else
				ret = sh_traverse_and_or_process_phase(child, context, phase);
			if (sh_verbose_traverse())
				ft_dprintf(2, BLUE
				"AND_OR : %s : returned value : %s\n"EOC, t_phase_name(phase), ret_to_str(ret));
			phase++;
			if (ret == KEEP_READ)
				continue ;
			if (ret == STOP_CMD_LINE)
				return (STOP_CMD_LINE);
			if (ret == ERROR)
			{
				if (phase - 1 == E_TRAVERSE_PHASE_EXPANSIONS)
					break ;
				else
					set_failed_command(context);
				continue ;
			}
		}
		if ((ptr = (ptr)->next))
		{
			ft_dprintf(2, RED"prev symbol : %s\n"EOC, ((t_ast_node*)ptr->content)->symbol->debug);
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
			ft_dprintf(2, BLUE
			"%s : %s : start\n"EOC, node->symbol->debug, t_phase_name(context->phase));
		return (sh_traverse_tools_browse(node, context));
	}
	else if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		return (sh_traverse_and_or_launch_phase(node, context));
	}
	else
	{
		if (sh_verbose_traverse())
			ft_dprintf(2, RED
			"%s : %s : start : SHOULD NOT HAPPEN\n"EOC, node->symbol->debug, t_phase_name(context->phase));
		return (sh_traverse_tools_browse(node, context));
	}
}
