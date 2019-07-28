/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/28 22:53:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_traverse_list_launch_phase(t_ast_node *child, t_context *context, t_phase phase)
{
	int		ret;

	context->phase = phase;
	ret = g_grammar[child->symbol->id].traverse(child, context);
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

static int	sh_traverse_list_redir_exec(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;
	t_phase		phase;

	ptr = node->children;
	while (ptr != NULL && context->shell->running)
	{
		child = (t_ast_node *)ptr->content;
		if ((ptr = (ptr)->next))
			ptr = (ptr)->next;
		phase = E_TRAVERSE_PHASE_EXPANSIONS;
		while (phase <= E_TRAVERSE_PHASE_EXECUTE)
		{
			if (sh_verbose_traverse())
				ft_dprintf(2, BLUE
				"traverse : LIST : %s : start\n"EOC, t_phase_name(phase));
			ret = sh_traverse_list_launch_phase(child, context, phase);
			if (sh_verbose_traverse())
				ft_dprintf(2, BLUE
				"traverse : LIST : %s : returned value : %d\n"EOC, t_phase_name(phase), ret);
			phase++;
			if (ret == KEEP_READ)
				continue ;
			if (ret == STOP_CMD_LINE)
				return (ERROR);
			if (ret == ERROR)
			{
				if (phase - 1 == E_TRAVERSE_PHASE_EXPANSIONS)
					break ;
				else
					set_failed_command(context);
				continue ;
			}
			return (ret);
		}
	}
	return (SUCCESS);
}

int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE
			"traverse : LIST : %s : start\n"EOC, t_phase_name(context->phase));
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		ret = sh_traverse_list_redir_exec(node, context);
		return (ret);
	}
}
