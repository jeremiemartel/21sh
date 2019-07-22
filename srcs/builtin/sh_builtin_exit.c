/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/22 23:34:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_exit(t_context *context)
{
	int		ret;

	if (context->params->tbl[1] && context->params->tbl[2])
		return (sh_perror_err_fd(context->fd[FD_ERR],
		context->params->tbl[0], SH_ERR1_TOO_MANY_ARGS));
	else if (context->params->tbl[1])
		ret = ft_atoi(context->params->tbl[1]) & 0xff;
	else
		ret = 0;
	if (sh_verbose_builtin())
		ft_dprintf(
			context->fd[FD_ERR], "exit: exit value setted to : %d\n", ret);
	sh_env_update_ret_value(context->shell, ret);
	context->shell->running = 0;
	return (SUCCESS);
}
