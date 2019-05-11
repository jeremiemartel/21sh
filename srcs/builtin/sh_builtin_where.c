/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_where.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:09:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/11 17:31:22 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_where(t_context *context)
{
	int		i;

	i = 1;
	ft_dprintf(2, RED"Where builtin is not fully impplemented, it can only show builtins\n"EOC);
	context->params->tbl++;
	while (*context->params->tbl)
	{
		if (sh_builtin_find(context))
			ft_printf("%s: %s built-in command\n",context->params->tbl[0] , SH_NAME);
		context->params->tbl++;
		i++;
	}
	context->params->tbl -= i - 1;
	return (SUCCESS);
}
