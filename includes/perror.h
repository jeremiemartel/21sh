/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:47:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/13 15:11:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERROR_H
# define PERROR_H

# include "sh_21.h"

# define SH_NAME		"21sh"
# define SH_ERR_COLOR	COLOR_PINK

# define SH_ERR1_MALLOC	"Malloc error occured"

/*
** ft_perror.c
*/
int		ft_perror(const char *error, const char *s1);
void	*ft_perrorn(const char *error, const char *s1);
int		ft_perror2(const char *error, const char *s1, const char *s2);
void	*ft_perror2n(const char *error, const char *s1, const char *s2);

#endif
