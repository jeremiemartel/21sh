/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/15 17:52:04 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_exit(t_context *context)
{
	if (context->params->tbl[1] && context->params->tbl[2])
		return (sh_perror_err_fd(context->fd[FD_ERR],
		context->params->tbl[0], SH_ERR1_TOO_MANY_ARGS));
	else if (context->params->tbl[1])
		context->shell->exit_value = ft_atoi(context->params->tbl[1]) & 0xff;
	context->shell->running = 0;
	return (SUCCESS);
}
