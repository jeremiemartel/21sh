/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 11:07:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_perror(const char *error, const char *suffix)
{
	if (suffix && *suffix)
		ft_dprintf(2, "%s%s: %s : %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(2, "%s%s: %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, COLOR_END);
	return (FAILURE);
}

int		sh_perror_err(const char *error, const char *suffix)
{
	sh_perror(error, suffix);
	return (ERROR);
}

void	*sh_perrorn(const char *error, const char *suffix)
{
	sh_perror(error, suffix);
	return (NULL);
}

int		sh_perror_fd(int fd, const char *error, const char *suffix)
{
	if (suffix && *suffix)
		ft_dprintf(fd, "%s%s: %s : %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(fd, "%s%s: %s%s\n", SH_ERR_COLOR, SH_NAME, error, COLOR_END);
	return (FAILURE);
}

int		sh_perror_err_fd(int fd, const char *error, const char *suffix)
{
	sh_perror_fd(fd, error, suffix);
	return (ERROR);
}

void	*sh_perrorn_fd(int fd, const char *error, const char *suffix)
{
	sh_perror_fd(fd, error, suffix);
	return (NULL);
}
