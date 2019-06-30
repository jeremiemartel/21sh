/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_assigment_word.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:11:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/30 16:22:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_assigment_word(t_ast_node *node, t_context *context)
{
	if (ft_strnstr(node->token->value, "PATH=", 5))
		process_builtin_hash_suppr_all(context->shell);
	return (sh_vars_assignment(context->env, context->vars,
				node->token->value));
}
