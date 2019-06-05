/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/05 15:30:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_traverse_cmd_word(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;

	if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		child = (t_ast_node *)node->children->content;
		if (child->token->id == LEX_TOK_WORD)
			sh_expansions(context, child); //return failure
		return (SUCCESS);
	}
	return (sh_traverse_cmd_name(node, context));
}
