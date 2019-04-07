/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:41:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/07 18:41:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		op_nothing(t_ast_node *node)
{
	(void)node;
	return (0);
}

int		op_plus(t_ast_node *node)
{
	return (sh_traverse(node->children->content) + sh_traverse(node->children->next->content));
}

int		op_mult(t_ast_node *node)
{
	return (sh_traverse(node->children->content) * sh_traverse(node->children->next->content));
}

int		op_int(t_ast_node *node)
{
	return (node->token->token_union.ival);
}

static  int (*g_operator_token[NB_TERMS - 1])
	(t_ast_node *) =
{
	op_nothing,
	op_nothing,
	op_plus,
	op_mult,
	op_int,
};

int		sh_traverse(t_ast_node *node)
{
	return ((g_operator_token[node->token->token_id])(node));
}
