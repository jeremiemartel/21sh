/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_reset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:45:22 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/17 11:25:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_traverse_tools_reset_std(t_context *context)
{
	context->fd[0] = 0;
	context->fd[1] = 1;
	context->fd[2] = 2;
};

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
	return ;
};
