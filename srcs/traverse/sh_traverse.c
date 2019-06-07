/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 03:23:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_traverse(t_shell *shell)
{
	t_context	context;
	int			ret;

	if (t_context_init(&context, shell) == FAILURE)
		return (FAILURE);
	context.phase = E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS;
	if ((ret = g_grammar[shell->parser.ast_root->symbol->id].
		traverse(shell->parser.ast_root, &context)))
	{
		ft_dy_tab_del(context.params);
		return (SUCCESS);
	}
	context.phase = E_TRAVERSE_PHASE_REDIRECTIONS;
	g_grammar[shell->parser.ast_root->symbol->id].
		traverse(shell->parser.ast_root, &context);
	t_context_free(&context);
	return (SUCCESS);
}
