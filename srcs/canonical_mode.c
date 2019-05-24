/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/24 12:14:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_canonical_mode(t_shell *shell)
{
	int         gnl_ret;
	t_gnl_info  info;
	int			ret;

	while ((gnl_ret = get_next_line2(0, &info)) == 1)
	{
		if (info.separator != E_SEPARATOR_ZERO)
		{
			if ((ret = (sh_process_command(shell, info.line)) != SUCCESS))
				return (ret);
		}
		else
		{
			free(info.line);
			return (ft_perror("Illegal characters received from input",
					"sh_process_canonical_mode"));
		}
		free(info.line);
	}
	if (gnl_ret == -1)
		return (ft_perror("get_next_line error", "sh_process_canonical_mode"));
	free(info.line);
	return (gnl_ret);
}
