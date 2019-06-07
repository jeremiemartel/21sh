/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 03:00:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh_21.h"

int		ft_perror2(const char *error, const char *prefix, const char *suffix)
{
	ft_dprintf(2, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	return (FAILURE);
}

void	*ft_perror2n(const char *error, const char *prefix, const char *suffix)
{
	ft_perror2(error, prefix, suffix);
	return (NULL);
}

int		ft_perror2_fd(int fd, const char *error, const char *prefix,
			const char *suffix)
{
	ft_dprintf(fd, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	return (FAILURE);
}

void	*ft_perror2n_fd(int fd, const char *error, const char *prefix,
			const char *suffix)
{
	ft_dprintf(fd, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	return (NULL);
}
