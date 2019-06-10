/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_assigment_word.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:11:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/09 19:44:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_assigment_word(t_ast_node *node, t_context *context)
{
	return (sh_vars_assignment(context->env, context->vars,
				node->token->value));
}
