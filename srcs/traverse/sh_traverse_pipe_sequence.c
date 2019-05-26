/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 09:30:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
//	t_ast_node		*child;
//	int				father;
	
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		return (SUCCESS);
	else
		return (sh_traverse_tools_browse(node, context));
}
