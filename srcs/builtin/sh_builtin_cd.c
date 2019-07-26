/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/26 02:38:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_cd(t_context *context)
{
	char	*param;
	char	*curpath;
	char	flags;
	int		i;
	int		ret;

	i = 1;
	curpath = NULL;
	if ((ret = sh_builtin_cd_parser(context, &i, &flags, &curpath)))
		return (ret);
	param = context->params->tbl[i];
	if ((ret = sh_builtin_cd_pre_rules(context, param, &curpath)))
		return (ret);
	if (flags & CD_OPT_HYPHEN)
	{
		free(context->params->tbl[i]);
		if (!(context->params->tbl[i] = ft_strdup(curpath)))
		{
			if (curpath)
				free(curpath);
			return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd"));
		}
	}
	if (!(flags & CD_OPT_PHYSIC))
	{
		sh_builtin_cd_rule7(context, &curpath, flags);
		sh_builtin_cd_rule8_1(&curpath);
	}
	ret = sh_builtin_cd_rule10(context, curpath, flags, param);
	free(curpath);
	return (ret);
}
