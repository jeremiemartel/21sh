/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:18:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/22 08:45:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_hash_usage(t_context *context, char *invalid_opt)
{
	sh_env_update_ret_value(context->shell, 2);
	if (invalid_opt)
		sh_perror2_err_fd(context->fd[FD_ERR],
		invalid_opt, "hash", SH_ERR2_INVALID_OPT);
	sh_perror_fd(context->fd[FD_ERR], "hash", "usage: hash [-r] [utility...]");
	return (ERROR);
}

static int	sh_builtin_hash_process_utilities(t_context *context, int i)
{
	int		ret;

	while (context->params->tbl[i])
	{
		ret = sh_builtin_hash_add_utility(context, context->params->tbl[i]);
		if (ret == FAILURE)
			return (FAILURE);
		else if (ret == ERROR)
			sh_env_update_ret_value(context->shell, ret);
		i++;
	}
	return (SUCCESS);
}

int			sh_builtin_hash(t_context *context)
{
	int		i;
	int		ret;

	if (context->params->current_size == 1)
	{
		sh_builtin_hash_show(context->shell);
		return (SUCCESS);
	}
	i = 1;
	ret = 0;
	while (context->params->tbl[i]
		&& ((char**)context->params->tbl)[i][0] == '-')
	{
		if (ft_strequ(((char**)context->params->tbl)[i], "-r"))
			ret = 1;
		else
			return (sh_builtin_hash_usage(context, context->params->tbl[i]));
		i++;
	}
	if (ret)
		sh_builtin_hash_empty_table(context->shell);
	return (sh_builtin_hash_process_utilities(context, i));
}
