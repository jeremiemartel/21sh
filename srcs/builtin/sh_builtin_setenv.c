/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:32:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 18:32:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_setenv(t_context *context)
{
	int i;
	int len;

	len = context->params->current_size;
	i = 1;
	while (i < len)
	{
		if (sh_process_setenv_equal((char *)(context->params->tbl[i]),
				context->env, context) == -1)
			return (-1);
		i++;
	}
	return (1);
}
