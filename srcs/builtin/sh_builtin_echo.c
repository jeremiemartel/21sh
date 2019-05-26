/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:57:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 17:01:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_echo(t_context *context)
{
	int i;

	if (!context->params->tbl[1])
	{
		ft_putchar_fd('\n', FD_OUT);
		return (SUCCESS);
	}
	i = 1;
	if (ft_strequ(context->params->tbl[1], "-n"))
		i++;
	while (context->params->tbl[i + 1])
	{
		ft_putstr_fd(context->params->tbl[i], FD_OUT);
		ft_putchar_fd(' ', FD_OUT);
		i++;
	}
	ft_putstr_fd(context->params->tbl[i], FD_OUT);
	if (!ft_strequ(context->params->tbl[1], "-n"))
		ft_putchar_fd('\n', FD_OUT);
	return (SUCCESS);
}
