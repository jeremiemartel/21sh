/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh_21.h"

int		sh_perror2(const char *error, const char *prefix, const char *suffix)
{
	ft_dprintf(2, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	return (FAILURE);
}

int		sh_perror2_err(const char *error, const char *prefix, const char *suffix)
{
	sh_perror2(error, prefix, suffix);
	return (ERROR);
}

void	*sh_perror2n(const char *error, const char *prefix, const char *suffix)
{
	sh_perror2(error, prefix, suffix);
	return (NULL);
}

int		sh_perror2_fd(int fd, const char *error, const char *prefix,
			const char *suffix)
{
	ft_dprintf(fd, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	return (FAILURE);
}

int		sh_perror2_err_fd(int fd, const char *error, const char *prefix, const char *suffix)
{
	sh_perror2_fd(fd, error, prefix, suffix);
	return (ERROR);
}

void	*sh_perror2n_fd(int fd, const char *error, const char *prefix, const char *suffix)
{
	ft_dprintf(fd, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	if (suffix && *suffix)
		ft_dprintf(fd, "%s%s: %s : %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(fd, "%s%s: %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, COLOR_END);
	return (NULL);
}
