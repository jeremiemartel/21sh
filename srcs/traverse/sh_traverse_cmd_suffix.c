/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_suffix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/17 00:15:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_traverse_cmd_suffix(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	t_list		*ptr;
	int			ret;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
		{
			if (child && child->token && child->token->expansion)
				if ((ret = sh_expansions(context, child)) != SUCCESS)
					return (ret);
		}
		if (context->phase == E_TRAVERSE_PHASE_EXECUTE && child->token)
		{
			if (!(!*child->token->value && child->token->expansion))
				if (ft_dy_tab_add_str(context->params, child->token->value))
					return (sh_perror(SH_ERR1_MALLOC, "sh_traverse_cmd_suffix"));
		}
		else if ((ret = g_grammar[child->symbol->id].
			traverse(child, context)))
			return (ret);
		ptr = ptr->next;
	}
	return (SUCCESS);
}
