/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_context.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 18:56:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


int		t_context_init(t_context *context, t_shell *shell)
{
	if (!(context->params = ft_dy_tab_new(5)))
		return (ft_perror(SH_ERR1_MALLOC, "t_context_init"));
	context->shell = shell;
	context->env = shell->env;
	context->vars = shell->vars;
	context->term = &shell->term;
	context->fd[0] = 0;
	context->fd[1] = 1;
	context->fd[2] = 2;
	context->pipe[PIPE_OUT] = 0;
	context->pipe[PIPE_IN] = 1;
	context->builtin = NULL;
	return (SUCCESS);
}

void	t_context_free(t_context *context)
{
	ft_dy_tab_del(context->params);
}
