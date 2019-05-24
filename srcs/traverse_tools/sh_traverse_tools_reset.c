/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_reset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:45:22 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/24 14:01:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_traverse_tools_reset_context(t_context *context)
{
	sh_traverse_tools_reset_params(context);
	sh_traverse_tools_close_fd(context);
	sh_traverse_tools_reset_fd(context);

}

void	sh_traverse_tools_close_fd(t_context *context)
{
	if (context->fd[0] != 0)
		close(context->fd[0]);
	if (context->fd[1] != 1)
		close(context->fd[1]);
	if (context->fd[2] != 2)
		close(context->fd[2]);
	if (context->pipe[0] > 2)
		close(context->pipe[0]);
	if (context->pipe[1] > 2)
		close(context->pipe[1]);
}

void	sh_traverse_tools_reset_fd(t_context *context)
{
	context->fd[0] = 0;
	context->fd[1] = 1;
	context->fd[2] = 2;
	context->pipe[PIPE_OUT] = 0;
	context->pipe[PIPE_IN] = 1;
}

void	sh_traverse_tools_reset_params(t_context *context)
{
	int		i;

	i = 0;
	while (context->params->tbl[i])
	{
		free(context->params->tbl[i]);
		context->params->tbl[i] = NULL;
		i++;
	}
	context->params->current_size = 0;
	if (context->path)
		ft_strdel(&context->path);
	return ;
}
