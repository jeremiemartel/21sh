/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:57:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/11 14:41:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_echo(t_context *context)
{
	int i;

	// ft_dprintf(2, YELLOW"Entering echo\nfdout : %d\n"EOC, context->fd[FD_OUT]);
	// ft_dprintf(1, "Test : echo (0)\n");
	if (!context->params->tbl[1])
	{
		ft_putchar('\n');
		return (SUCCESS);
	}
	// ft_dprintf(2, YELLOW"echo (1)\n"EOC);
	// ft_dprintf(1, "Test : echo (1)\n");
	i = 1;
	if (ft_strequ(context->params->tbl[1], "-n"))
		i++;
	while (context->params->tbl[i + 1])
	{
		ft_putstr(context->params->tbl[i]);
		ft_putchar(' ');
		i++;
	}
	if (ft_strequ(context->params->tbl[1], "-n"))
		ft_putstr(context->params->tbl[i]);
	else
		ft_putstrn(context->params->tbl[i]);
	return (SUCCESS);
}
