/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/21 18:05:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_set(t_context *context)
{
	int		i;

	i = 0;
	while (context->env->tbl[i])
	{
		ft_putstr_fd(context->env->tbl[i], context->fd[FD_OUT]);
		ft_putchar_fd('\n', context->fd[FD_OUT]);
		i++;
	}
	i = 0;
	while (context->vars->tbl[i])
	{
		ft_putstr_fd(context->vars->tbl[i], context->fd[FD_OUT]);
		ft_putchar_fd('\n', context->fd[FD_OUT]);
		i++;
	}
	return (SUCCESS);
}
