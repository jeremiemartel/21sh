/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:37:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 18:37:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h" 

int		sh_builtin_unsetenv(t_context *context)
{
	int i;

	if (context->params->current_size == 1)
		return (1);
	else
	{
		i = 0;
		while (context->env->tbl[i])
		{
			if (is_key_of_entry(context->env->tbl[i], context->params->tbl[1]))
			{
				ft_dy_tab_suppr_index(context->env, i);
				break ;
			}
			i++;
		}
	}
	return (SUCCESS);
}
