/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/26 00:14:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_traverse_and_or_execute_process(t_list **ptr,
		int *prev_symbol, t_context *context)
{
	t_ast_node	*child;
	int			ret;

	if (*prev_symbol != -1
			&& ((*prev_symbol == sh_index(LEX_TOK_AND_IF)
				&& context->shell->ret_value)
					|| (*prev_symbol == sh_index(LEX_TOK_OR_IF)
						&& !context->shell->ret_value)))
		return (SUCCESS);
	child = (t_ast_node *)(*ptr)->content;
	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (ret == FAILURE || ret == STOP_CMD_LINE)
		return (ret);
	if (!context->shell->running)
		return (SUCCESS);
	if ((*ptr = (*ptr)->next))
	{
		*prev_symbol = ((t_ast_node *)((*ptr)->content))->symbol->id;
		*ptr = (*ptr)->next;
	}
	return (KEEP_READ);
}

static int		sh_traverse_and_or_execute(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	int			ret;
	int			prev_symbol;

	prev_symbol = -1;
	ptr = node->children;
	while (ptr != NULL)
	{
		if (sh_verbose_traverse())
		{
			ft_dprintf(2, BLUE"traverse : execute : %s\n"EOC,
				node->symbol->debug);
		}
		if ((ret = sh_traverse_and_or_execute_process(&ptr,
			&prev_symbol, context)) != KEEP_READ)
			return (ret);
	}
	return (SUCCESS);
}

int				sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
		return (sh_traverse_and_or_execute(node, context));
	else
		return (sh_traverse_tools_browse(node, context));
}
