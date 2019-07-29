/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 03:10:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_traverse_list_redir_exec(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	ptr = node->children;
	while (ptr != NULL && context->shell->running)
	{
		child = (t_ast_node *)ptr->content;
		if ((ptr = (ptr)->next))
			ptr = (ptr)->next;
		context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
		ret = g_grammar[child->symbol->id].traverse(child, context);
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE"LIST : %s : returned value : %s\n"EOC, t_phase_name(context->phase), ret_to_str(ret));
		if (ret == FAILURE)
			return (FAILURE);
		else if (ret == STOP_CMD_LINE)
			return (ERROR);
	}
	return (ret);
}

int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE
			"LIST : %s : start\n"EOC, t_phase_name(context->phase));
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		if (sh_verbose_traverse())
			ft_dprintf(2, BLUE
			"%s : %s : start\n"EOC, node->symbol->debug, t_phase_name(context->phase));
		ret = sh_traverse_list_redir_exec(node, context);
		return (ret);
	}
}
