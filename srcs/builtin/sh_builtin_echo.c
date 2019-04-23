/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:57:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/23 12:00:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_echo(t_dy_tab *argv, t_dy_tab *env)
{
	int i;

	if (!argv->tbl[1])
	{
		ft_putchar('\n');
		return (SUCCESS);
	}
	i = 1;
	if (ft_strequ(argv->tbl[1], "-n"))
		i++;
	while (argv->tbl[i + 1])
	{
		ft_putstr(argv->tbl[i]);
		ft_putchar(' ');
		i++;
	}
	if (ft_strequ(argv->tbl[1], "-n"))
		ft_putstr(argv->tbl[i]);
	else
		ft_putstrn(argv->tbl[i]);
	return (SUCCESS);
	(void)env;
}
