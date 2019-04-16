/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_flush.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:40:06 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/16 11:46:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_tools_flush(t_context *context)
{
	int		ret;
	int		i;

	ret = execute_command(context);
	i = 0;
	while (context->params->tbl[i])
	{
		free(context->params->tbl[i]);
		context->params->tbl[i] = NULL;
		i++;
	}
	context->params->current_size = 0;
	return (ret);
}
