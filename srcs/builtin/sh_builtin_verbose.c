/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_verbose.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:19:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 18:22:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_verbose_usage(t_context *context)
{
	ft_dprintf(context->fd[FD_ERR], "usage: verbose on/off [lexer,ast,pipe,exec]\n");
	return (FAILURE);
}

int			sh_builtin_verbose(t_context *context)
{
	int			i;
	int			j;
	char		value[3];
	static char	key[6][20] = {"verbose_ast", "verbose_lexer", "verbose_exec", "verbose_pipe", "verbose_expansion", ""};

	i = 2;
	if (ft_strequ(context->params->tbl[1], "on"))
		ft_strcpy(value, "on");
	else if (ft_strequ(context->params->tbl[1], "off"))
		ft_strcpy(value, "");
	else
		return (sh_builtin_verbose_usage(context));
	while (context->params->tbl[i])
	{
		j = 0;
		while (*key[j])
		{
			if (ft_strequ(context->params->tbl[i], key[j] + 8))
				sh_vars_assign_key_val(context->env, context->vars, key[j], value);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
