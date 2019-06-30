/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:07:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/30 15:52:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_env_parser_env_new:
**	Create a new env t_dy_tab.
**		If env is NULL : tab is returned empty;
**		Else : it is filled with env values.
**	The tab will be used to store modified environment.
**
**	return :
**		NULL if malloc failed
**		Address of the new dy_tab
*/

static t_dy_tab	*sh_builtin_env_parser_env_new(t_dy_tab *env)
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

/*
** sh_builtin_env_parser_param:
**	Create a new t_dy_tab, cloning a t_dy_tab, after a given offset.
**	This new dy_tab is stored in new.
**	It is used keep the command to execute, without env parameters.
**
**	returned Values:
**		FAILURE : Malloc error
**		SUCCESS: new var had been updated
*/

static int		sh_builtin_env_parser_param(
	t_dy_tab *params, t_dy_tab **new, int offset, int fd_err)
{
	int			i;

	i = offset;
	if (!(*new = ft_dy_tab_new(params->current_size + 1)))
	{
		sh_perror_fd(
			fd_err, SH_ERR1_MALLOC, "sh_builtin_env_init_new_params (1)");
		return (FAILURE);
	}
	while (params->tbl[i])
	{
		if (ft_dy_tab_add_str(*new, params->tbl[i]))
		{
			ft_dy_tab_del(*new);
			return (sh_perror_fd(
				fd_err, SH_ERR1_MALLOC, "sh_builtin_env_init_new_params (2)"));
		}
		i++;
	}
	return (SUCCESS);
}

/*
** sh_builtin_env_parser_env:
**	Read assginemnts given as params and modify the environnemnt accordingly.
**
**	returned Values:
**		FAILURE : Malloc error
**		ERROR : Invalid assignment
**		SUCCESS : new var had been updated
*/

static int		sh_bultin_env_parser_env_assign(
	t_context *context, t_dy_tab **new_env, int *i, char **params)
{
	int		ret;

	while (params[*i] && ft_strchr(params[*i], '='))
	{
		if ((ret = sh_builtin_setenv_process(
			params[*i], *new_env, context)) != SUCCESS)
		{
			if (ret == ERROR)
				sh_builtin_env_usage(context->fd[FD_ERR]);
			ft_dy_tab_del(*new_env);
			*new_env = NULL;
			return (ret);
		}
		*i += 1;
	}
	return (SUCCESS);
}

/*
** sh_builtin_env_parser_env:
**	Create a new t_dy_tab, using options given as params.
**	This new dy_tab is stored in new_env.
**	If the -i option is given new env is empty when created. Else,
**	it is cloned from current env.
**	This env will be given to the son process, or will be printed.
**
**	returned Values:
**		FAILURE : Malloc error
**		ERROR : Invalid option or assignment
**		SUCCESS: new var had been updated
*/

static int		sh_builtin_env_parser_env(
	t_context *context, t_dy_tab **new_env, int *i, char **params)
{
	while (params[*i] && params[*i][0] == '-')
	{
		if (params[*i][1] != 'i')
		{
			sh_perror2_err_fd(
				context->fd[FD_ERR], SH_ERR2_INVALID_OPT, "env", params[*i]);
			sh_builtin_env_usage(context->fd[FD_ERR]);
			return (ERROR);
		}
		if (!*new_env)
			*new_env = sh_builtin_env_parser_env_new(NULL);
		*i += 1;
	}
	if (*i == 1)
		*new_env = sh_builtin_env_parser_env_new(context->env);
	if (!*new_env)
	{
		sh_perror_fd(
			context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_env_parser_env");
		return (FAILURE);
	}
	return (sh_bultin_env_parser_env_assign(context, new_env, i, params));
}

/*
** sh_builtin_env_parser:
**	Browse every env arguments creating the new_env dy_tab.
**
**	returned Values:
**		FAILURE : malloc error
**		ERROR : Invalid Option
**		SUCCESS : new_env had been successfully malloced and filled
*/

int				sh_builtin_env_parser(
	t_context *context, t_dy_tab **new_env, t_dy_tab **new_param)
{
	int		ret;
	char	**params;
	int		i;

	i = 1;
	*new_env = NULL;
	*new_param = NULL;
	params = (char**)context->params->tbl;
	ret = sh_builtin_env_parser_env(context, new_env, &i, params);
	if (ret != SUCCESS)
		return (ret);
	ret = sh_builtin_env_parser_param(
		context->params, new_param, i, context->fd[FD_ERR]);
	return (ret);
}
