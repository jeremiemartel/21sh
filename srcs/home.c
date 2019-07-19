/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:46:13 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/19 10:02:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*get_home_dup(t_shell *shell)
{
	char			*str;
	struct passwd	*pwd;
	uid_t			uid;

	if (!(str = sh_vars_get_value(shell->env, NULL, "HOME")))
	{
		uid = geteuid();
		if (!(pwd = getpwuid(uid)))
			return (NULL);
		else
			return (ft_strdup(pwd->pw_dir));
	}
	else
		return (ft_strdup(str));
}

int		process_subst_home(t_shell *shell, char **str)
{
	char *subst;

	if (!(subst = get_home_dup(shell)))
		return (sh_perror(SH_ERR1_MALLOC, "process_subst_home"));
	else if (ft_substitute_str(str, subst, 0, 1))
	{
		free(subst);
		return (sh_perror(SH_ERR1_MALLOC, "process_subst_home"));
	}
	free(subst);
	return (SUCCESS);
}
