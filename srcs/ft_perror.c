/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/13 15:12:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh_21.h"

int		ft_perror(const char *error, const char *s1)
{
	ft_dprintf(2, "%s%s: %s : %s%s\n", SH_ERR_COLOR, SH_NAME, error, s1, COLOR_END);
	return (FAILURE);
}

void	*ft_perrorn(const char *error, const char *s1)
{
	ft_perror(error, s1);
	return (NULL);
}

int		ft_perror2(const char *error, const char *s1, const char *s2)
{
	ft_dprintf(2, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, s1, error, s2, COLOR_END);
	return (FAILURE);
}

void	*ft_perror2n(const char *error, const char *s1, const char *s2)
{
	ft_perror2(error, s1, s2);
	return (NULL);
}
