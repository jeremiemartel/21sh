/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:57:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 17:37:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_echo(t_context *context)
{
	int i;

	if (!context->params->tbl[1])
	{
		ft_putchar('\n');
		return (SUCCESS);
	}
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
