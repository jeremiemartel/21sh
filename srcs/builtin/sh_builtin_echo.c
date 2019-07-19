/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:57:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/19 08:54:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_echo_write(t_context * context, char *str)
{
	int		len;
	int		ret;

	len = ft_strlen(str);
	ret = write(context->fd[FD_OUT], str, len);
	if (ret == -1)
	{
		return (sh_perror2_err_fd(context->fd[FD_ERR], "echo", "write error",
			SH_ERR1_BAD_FD));
	}
	return (SUCCESS);
}

int		sh_builtin_echo(t_context *context)
{
	int		i;
	int		ret;

	if (!context->params->tbl[1])
		return (sh_builtin_echo_write(context, "\n"));
	i = 1;
	while (context->params->tbl[i] && ft_strequ(context->params->tbl[i], "-n"))
		i++;
	ret = 0;
	while (!ret && context->params->tbl[i + 1])
	{
		ret = sh_builtin_echo_write(context, context->params->tbl[i]);
		if (!ret)
			ret = sh_builtin_echo_write(context, " ");
		i++;
	}
	if (ret)
		return (ERROR);
	if (sh_builtin_echo_write(context, context->params->tbl[i]) == ERROR)
		return (ERROR);
	if (!ft_strequ(context->params->tbl[1], "-n"))
		return (sh_builtin_echo_write(context, "\n"));
	return (SUCCESS);
}
