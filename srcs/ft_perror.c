/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 03:01:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh_21.h"

int		ft_perror(const char *error, const char *suffix)
{
	if (suffix && *suffix)
		ft_dprintf(2, "%s%s: %s : %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(2, "%s%s: %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, COLOR_END);
	return (FAILURE);
}

void	*ft_perrorn(const char *error, const char *suffix)
{
	ft_perror(error, suffix);
	return (NULL);
}

int		ft_perror_fd(int fd, const char *error, const char *suffix)
{
	if (suffix && *suffix)
		ft_dprintf(fd, "%s%s: %s : %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(fd, "%s%s: %s%s\n", SH_ERR_COLOR, SH_NAME, error, COLOR_END);
	return (FAILURE);
}

void	*ft_perrorn_fd(int fd, const char *error, const char *suffix)
{
	if (suffix && *suffix)
		ft_dprintf(fd, "%s%s: %s : %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(fd, "%s%s: %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, COLOR_END);
	return (NULL);
}
