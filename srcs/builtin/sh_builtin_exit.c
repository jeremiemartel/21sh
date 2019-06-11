/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_exit(t_context *context)
{
	if (context->params->tbl[0] && context->params->tbl[1] && context->params->tbl[2])
		return (sh_perror(context->params->tbl[0], SH_ERR1_TOO_MANY_ARGS));
	else if (context->params->tbl[1])
	{
		context->shell->running = 0;
		return (ft_atoi(context->params->tbl[1]) + 0xF000); //WTF is that number ??
	}
	else
	{
		context->shell->running = 0;
		return (0xF000);
	}
}
