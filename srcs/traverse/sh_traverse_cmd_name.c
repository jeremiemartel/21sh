/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/19 16:16:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_traverse_cmd_name(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;

	child = (t_ast_node *)node->children->content;
	if (ft_dy_tab_add_str(context->params, ft_strtolower(child->token->value)))
		return (FAILURE);
	return (SUCCESS);
}
