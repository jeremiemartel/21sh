/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 17:04:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_set(t_context *context)
{
	int		i;

	i = 0;
	while (context->env->tbl[i])
	{
		ft_putstr_fd(context->env->tbl[i], FD_OUT);
		ft_putchar_fd('\n', FD_OUT);
		i++;
	}
	i = 0;
	while (context->vars->tbl[i])
	{
		ft_putstr_fd(context->vars->tbl[i], FD_OUT);
		ft_putchar_fd('\n', FD_OUT);
		i++;
	}
	return (SUCCESS);
}
