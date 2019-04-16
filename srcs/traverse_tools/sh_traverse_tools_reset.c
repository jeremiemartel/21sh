/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_reset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:45:22 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/16 15:58:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_traverse_tools_reset_std(t_context *context)
{
	context->std[0] = 0;
	context->std[1] = 1;
	context->std[2] = 2;
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
