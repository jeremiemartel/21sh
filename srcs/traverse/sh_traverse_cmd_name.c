/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_traverse_cmd_name(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;

	if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		child = (t_ast_node *)node->children->content;
		if (child && child->token && child->token->expansion)
			return (sh_expansions(context, child));
		return (SUCCESS);
	}
	else if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		child = (t_ast_node *)node->children->content;
		if (ft_dy_tab_add_str(context->params, child->token->value))
			return (sh_perror(SH_ERR1_MALLOC, "sh_traverse_cmd_name"));
		return (SUCCESS);
	}
	else
		return (SUCCESS);
}
