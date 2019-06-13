/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:04:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 16:15:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_builtin_container	*get_builtins(void)
{
	static t_builtin_container res[NB_BUILTINS] = {
		{ "echo", sh_builtin_echo },
		{ "pwd", sh_builtin_pwd },
		{ "exit", sh_builtin_exit },
		{ "where", sh_builtin_where },
		{ "cd", sh_builtin_cd },
		{ "verbose", sh_builtin_verbose },
		{ "set", sh_builtin_set },
		{ "hash", sh_builtin_hash },
		{ "unsetenv", sh_builtin_unsetenv },
		{ "setenv", sh_builtin_setenv },
		{ "env", sh_builtin_env }
	};
	return (res);
}

t_builtin			sh_builtin_find(t_context *context)
{
	int					i;
	t_builtin_container	*builtins;

	builtins = get_builtins();
	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strcmp(context->params->tbl[0], builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}
