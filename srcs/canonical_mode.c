/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/23 10:34:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_read_separator_others(char **command, t_gnl_info  info)
{
	if (info.separator == E_SEPARATOR_ZERO)
		return (ft_perror("Illegal characters received from input",
					"sh_process_read_separator_others"));
	else if (!(*command = ft_strjoin_free(*command, info.line, 1)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_canonical_mode"));
	return (SUCCESS);
}

int		sh_process_read_separator_new_line(char **command, t_gnl_info  info)
{
	if (!(*command = ft_strjoin_free(*command, info.line, 1)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_canonical_mode"));
	if (!(*command = ft_strjoin_free(*command, "\n", 1)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_canonical_mode"));
	return (SUCCESS);
}

/*
int		sh_process_canonical_mode(t_shell *shell)
{
	int         gnl_ret;
	char		*command;
	t_gnl_info  info;
	int			ret;

	if (!(command = ft_strnew(0)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_canonical_mode"));
	while ((gnl_ret = get_next_line2(0, &info)) == 1)
	{
		if (info.separator == E_SEPARATOR_NL)
		{
			if (sh_process_read_separator_new_line(&command, info) != SUCCESS)
				return (ft_free_turn(info.line, FAILURE));
		}
		else
		{
			if (sh_process_read_separator_others(&command, info) != SUCCESS)
				return (ft_free_turn(info.line, FAILURE));
		}
		free(info.line);
	}
	free(info.line);
	ret = (sh_process_command(shell, command));
	return (ret);
}
*/

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
					"sh_process_read_separator_others"));
		}
		free(info.line);
	}
	if (gnl_ret == -1)
		return (ft_perror("get_next_line error", "sh_process_canonical_mode"));
	free(info.line);
	return (gnl_ret);
}
