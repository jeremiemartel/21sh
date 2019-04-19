/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/19 20:34:34 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_context(t_context *context, t_shell *shell)
{
	if (!(context->params = ft_dy_tab_new(5)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_init_context"));
	context->env = shell->env;
	context->term = &shell->term;
	context->fd[0] = 0;
	context->fd[1] = 1;
	context->fd[2] = 2;
	context->pipe[PIPE_OUT] = 0;
	context->pipe[PIPE_IN] = 1;
	return (SUCCESS);
}

void	sh_free_context(t_context *context)
{
	ft_dy_tab_del(context->params);
}

int		sh_process_traverse(t_shell *shell)
{
	t_context	context;

	if (sh_init_context(&context, shell) == FAILURE)
		return (FAILURE);
	g_grammar[shell->parser.ast_root->symbol->id].
		traverse(shell->parser.ast_root, &context);
	// ft_strtab_put((char **)context.params->tbl);
	sh_free_context(&context);
	return (SUCCESS);
}
