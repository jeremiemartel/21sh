/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:39:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/29 17:51:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_env(t_context *context)
{
	t_dy_tab	*new_env;
	t_dy_tab	*new_param;
	int			ret;
	t_dy_tab	*save_env;
	t_dy_tab	*save_params;

	if ((ret = sh_builtin_env_parser(context, &new_env, &new_param)))
	{
		// leaks !
		return (ret);
	}
	context->builtin = NULL;
	save_env = context->env;
	save_params = context->params;
	context->params = new_param;
	if (!(context->params->tbl[0]))
	{
		context->env = new_env;
		ret = sh_builtin_env_no_args(context);
		context->env = save_env;
	}
	else
		ret = sh_builtin_env_process_command(context, new_env);
	ft_dy_tab_del(new_env);
	ft_dy_tab_del(context->params);
	context->env = save_env;
	context->params = save_params;
	return (ret);
}
