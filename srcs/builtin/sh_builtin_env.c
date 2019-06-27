/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:39:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/25 16:29:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_env_no_args:
**	Print current environment on stdout, used when env is called with no args.
**
**	return SUCCESS
*/

static int	sh_builtin_env_no_args(t_context *context)
{
	size_t		i;
	t_dy_tab	*env;

	env = context->env;
	i = 0;
	while (i < env->current_size)
	{
		ft_dprintf(context->fd[FD_OUT], "%s\n", env->tbl[i]);
		i++;
	}
	return (SUCCESS);
}

/*
** sh_builtin_env_init_new_env:
**	Create a new env t_dy_tab.
**		If env is NULL : tab is returned empty;
**		Else : it is filled with env values.
**	The tab will be used to store modified environment.
**
**	return :
**		NULL if malloc failed
**		Address of the new dy_tab
*/

static t_dy_tab	*sh_builtin_env_init_new_env(t_dy_tab *env)
{
	int			len;
	int			i;
	t_dy_tab	*tbl;

	if (!env)
	{
		if (!(tbl = ft_dy_tab_new(3)))
			return (NULL);
		return (tbl);
	}
	len = env->current_size;
	if (!(tbl = ft_dy_tab_new(len + 5)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (ft_dy_tab_add_str(tbl, env->tbl[i]))
		{
			ft_dy_tab_del(tbl);
			return (NULL);
		}
		i++;
	}
	return (tbl);
}

static t_dy_tab	*sh_builtin_env_init_new_params(t_dy_tab *params, int offset)
{
	int			i;
	t_dy_tab	*new;

	i = offset;
	if (!(new = ft_dy_tab_new(params->current_size + 1)))
		return (NULL);
	while (params->tbl[i])
	{
		if (ft_dy_tab_add_str(new, params->tbl[i]))
		{
			ft_dy_tab_del(new);
			return (NULL);
		}
		i++;
	}
	return (new);
}

static int	sh_builtin_env_process_command(t_context *context)
{
	int		ret;

	if (!context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_traverse_sc_no_slash_cmd(context);
	else
	{
		if (!(context->path = ft_strdup(context->params->tbl[0])))
			return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_env_process_command"));
		if (sh_traverse_sc_check_perm(context->path, context->params->tbl[0]) != SUCCESS)
			ret = ERROR;
		else
			ret = sh_process_execute(context);
	}
	return (ret);
}

int			sh_builtin_env(t_context *context)
{
	int			i;
	char		**params;
	t_dy_tab	*new_env;
	int			ret;

	params = (char**)context->params->tbl;
	if (!params[1] || !params[1][0])
		return (sh_builtin_env_no_args(context));
	i = 1;
	if (params[i] && ft_strequ(params[i], "-i"))
	{
		new_env = sh_builtin_env_init_new_env(NULL);
		i++;
	}
	else
		new_env = sh_builtin_env_init_new_env(context->env);
	if (!new_env)
		return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_main_init_env"));

	while (params[i] && ft_strchr(params[i], '='))
	{
		if ((ret = sh_builtin_setenv_process(params[i], new_env, context)) != SUCCESS)
		{
			ft_dy_tab_del(new_env);
			return (ret); //leaks ?
		}
		i++;
	}

	t_dy_tab	*save_env;
	t_dy_tab	*save_params;
	
	save_env = context->env;
	save_params =context->params;


	context->env = new_env;
	context->params = sh_builtin_env_init_new_params(context->params, i);

	ret = SUCCESS;
	if (!context->params)
		ret = sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_main_init_params");
	if (!ret && !(context->params->tbl[0]))
		ret = sh_builtin_env_no_args(context);
	if (!ret)
		ret = sh_builtin_env_process_command(context);

	ft_dy_tab_del(new_env);
	ft_dy_tab_del(context->params);
	context->env = save_env;
	context->params = save_params;
	return (ret);
}
