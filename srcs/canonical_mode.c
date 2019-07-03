/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:06:46 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/03 23:31:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_process_read_canonical_gnl(t_shell *shell, t_gnl_info *info)
{
	int ret;

	if (info->separator != E_SEPARATOR_ZERO)
	{
		if ((ret = (sh_process_command(shell, info->line)) == FAILURE))
		{
//			ft_printf(RED"%s\n"EOC, info->line);
			free(info->line);
			return (ret);
		}
		if (sh_append_to_historic(shell, info->line) != SUCCESS)
		{
			free(info->line);
			return (FAILURE);
		}
	}
	else
	{
		free(info->line);
		return (sh_perror("Illegal characters received from input",
			"sh_process_read_canonical_gnl"));
	}
	free(info->line);
	return (SUCCESS);
}

static int		sh_process_read_canonical_mode(t_shell *shell)
{
	int			gnl_ret;
	t_gnl_info	info;
	int			ret;

	while ((gnl_ret = get_next_line2(0, &info)) == 1)
	{
//		ft_printf("%s\n", info.line);
		if ((ret = sh_process_read_canonical_gnl(shell, &info)))
		{
			return (FAILURE);
		}
	}
	if (gnl_ret == -1)
		return (sh_perror("get_next_line error", "sh_process_read_canonical"));
	free(info.line);
	return (SUCCESS);
}

int				sh_process_canonical_mode(t_shell *shell, char **env)
{
	int ret;

	if (sh_init_shell(shell, env) != SUCCESS)
	{
		sh_free_all(shell);
		return (FAILURE);
	}
	ret = sh_process_read_canonical_mode(shell);
	sh_free_all(shell);
	return (ret);
}
