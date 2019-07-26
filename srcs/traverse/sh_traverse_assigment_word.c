/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_assigment_word.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:11:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/27 00:51:16 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_assigment_word(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		if (node && node->token && node->token->expansion)
			return (sh_expansions(context, node));
		return (SUCCESS);
	}
	else if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		if (ft_strnstr(node->token->value, "PATH=", 5))
			sh_builtin_hash_empty_table(context->shell);
		return (sh_vars_assignment(context->env, context->vars,
					node->token->value));
	}
	else
		return (sh_traverse_tools_browse(node, context));
}
