/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here_canonical.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:29:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/21 16:24:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		process_heredoc_canonical_mode(t_gnl_info info,
				char **res, char *(*heredoc_func)(const char *), char *eof)
{
	char		*tmp;

	if (info.separator != E_SEPARATOR_ZERO)
	{
		if (!(tmp = heredoc_func(info.line)))
		{
			return (ft_free_turn_2(*res, info.line,
				sh_perror(SH_ERR1_MALLOC, "heredoc_canonical_mode")));
		}
		if (!ft_strcmp(tmp, eof))
			return (ft_free_turn_2(tmp, info.line, SUCCESS));
		free(info.line);
		if (!(*res = ft_strjoin_free(*res, tmp, 3)))
			return (sh_perror(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
		if (!(*res = ft_strjoin_free(*res, "\n", 1)))
			return (sh_perror(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
	}
	else
	{
		free(info.line);
		return (sh_perror("Illegal characters received from input",
					"heredoc_canonical_mode"));
	}
	return (3);
}

char			*heredoc_canonical_mode(char *eof,
			char *(*heredoc_func)(const char *), int *ret)
{
	int			gnl_ret;
	t_gnl_info	info;
	char		*res;

	if (!(res = ft_strnew(0)))
		return (sh_perrorn(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
	while ((gnl_ret = get_next_line2(0, &info, 1)) == 1)
	{
		if ((*ret = process_heredoc_canonical_mode(info,
				&res, heredoc_func, eof)) != 3)
		{
			if (*ret == SUCCESS)
				return (res);
			else
				return (NULL);
		}
	}
	if (gnl_ret == -1)
	{
		*ret = -2;
		return (ft_free_turn_str(&res, NULL));
	}
	free(info.line);
	*ret = SUCCESS;
	return (res);
}
