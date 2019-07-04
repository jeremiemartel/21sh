/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/04 02:48:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_exit(t_context *context)
{
	if (context->params->tbl[0] && context->params->tbl[1]
			&& context->params->tbl[2])
		return (sh_perror(context->params->tbl[0], SH_ERR1_TOO_MANY_ARGS));
	else if (context->params->tbl[1])
		context->shell->exit_value = ft_atoi(context->params->tbl[1]) & 0xff;
	context->shell->running = 0;
	if (isatty(0))
		ft_dprintf(context->fd[FD_ERR], "exit\n");
	return (SUCCESS);
}
