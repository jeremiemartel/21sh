/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:39:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/30 15:54:22 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_env_usage:
**	Display env builtin usage on a given fd.
*/

void			sh_builtin_env_usage(int fdout)
{
	sh_perror_fd(fdout, "usage", "env [-i]  [key=val] ... [utility [args]]");
}

/*
** sh_builtin_env:
**		Parse params to prepare new_env and new_param,
**		before sending it to sh_buitin_env_execute.
**
**	Returned Values:
**		FAILURE : Malloc error
**		ERROR : invalid option or assignment
**		Any returned value by the son process.
*/

static int		sh_buitin_env_execute(
	t_context *context, t_dy_tab *new_env, t_dy_tab *new_param)
{
	int			ret;
	t_dy_tab	*save_env;
	t_dy_tab	*save_params;

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

/*
**	env [-i] [key=val] ... [utility [args]]
**	The env utility shall obtain the current environment, modify it
**	according to its arguments, then invoke the utility
**	named by the utility.
**	If no utility operand is specified, the resulting environment is
**	written to the standard output, with one name=value pair per line.
**
** sh_builtin_env:
**		Parse params to prepare new_env and new_param,
**		before sending it to sh_buitin_env_execute.
**
**	Returned Values:
**		FAILURE : Malloc error
**		ERROR : invalid option or assignment
**		Any returned value by the son process.
*/

int				sh_builtin_env(t_context *context)
{
	t_dy_tab	*new_env;
	t_dy_tab	*new_param;
	int			ret;

	if ((ret = sh_builtin_env_parser(context, &new_env, &new_param)))
	{
		if (new_env)
			ft_dy_tab_del(new_env);
		if (new_param)
			ft_dy_tab_del(new_param);
		return (ret);
	}
	return (sh_buitin_env_execute(context, new_env, new_param));
}
