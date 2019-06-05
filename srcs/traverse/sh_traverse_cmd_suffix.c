/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_suffix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/05 22:46:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_traverse_cmd_suffix(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	t_list		*ptr;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
		{
			if (child && child->token && child->token->id == LEX_TOK_WORD)
				sh_expansions(context, child); //return failure
		}
		if (context->phase == E_TRAVERSE_PHASE_EXECUTE && child->token)
		{
			if (ft_dy_tab_add_str(context->params, child->token->value))
				return (FAILURE);
		}
		else if (g_grammar[child->symbol->id].traverse(child, context) == FAILURE)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}
