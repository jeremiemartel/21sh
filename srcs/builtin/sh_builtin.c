/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:04:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 19:04:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_find(t_context *context)
{
	if (!ft_strcmp(context->params->tbl[0], "echo"))
	{
		context->builtin = &sh_builtin_echo;
		return (SUCCESS);
	}
	else if (!ft_strcmp(context->params->tbl[0], "pwd"))
	{
		context->builtin = &sh_builtin_pwd;
		return (SUCCESS);
	}
	else if (!ft_strcmp(context->params->tbl[0], "exit"))
	{
		context->builtin = &sh_builtin_exit;
		return (SUCCESS);
	}
	return (FAILURE);
}
