/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:37:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/15 17:01:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_unsetenv(t_context *context)
{
	int i;

	if (context->params->current_size == 1)
		return (ERROR);
	else
	{
		i = 0;
		while (context->env->tbl[i])
		{
			if (is_key_of_entry(context->env->tbl[i], context->params->tbl[1]))
			{
				if (!ft_strcmp(context->params->tbl[1], "PATH"))
					process_builtin_hash_suppr_all(context->shell);
				ft_dy_tab_suppr_index(context->env, i);
				break ;
			}
			i++;
		}
	}
	return (SUCCESS);
}
