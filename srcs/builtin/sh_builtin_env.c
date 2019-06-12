/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:39:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 18:39:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_env(t_context *context)
{
	size_t i;
	t_dy_tab *env;

	env = context->env;
	i = 0;
	while (i < env->current_size)
	{
		ft_printf("%s\n", env->tbl[i]);
		i++;
	}
	return (SUCCESS);
}
