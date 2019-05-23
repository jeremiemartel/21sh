/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:47:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/23 15:04:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERROR_H
# define PERROR_H

# include "sh_21.h"

# define SH_NAME		"21sh"
# define SH_ERR_COLOR	COLOR_PINK

# define SH_ERR1_MALLOC			"Malloc error occured"
# define SH_ERR1_ENV_NOT_SET	"Environnement variable is not set"
# define SH_ERR1_TERM_CPY		"Could not copy terminal attributes"
# define SH_ERR1_INTERN_ERR		"System internal error"
# define SH_ERR1_CMD_NOT_FOUND	"Command not found"
# define SH_ERR1_HISTORIC		"Could not open the historic file"
# define SH_ERR1_PERM_DENIED	"Permission denied"
# define SH_ERR1_TOO_MANY_ARGS	"Too many arguments"
# define SH_ERR1_NOT_A_DIR		"Not a directory"
# define SH_ERR1_BAD_FD			"Bad file descriptor"
# define SH_ERR1_IS_DIR			"is a directory"
# define SH_ERR1_UNEXPECTED_EOF	"unexpected EOF"

# define SH_ERR2_NO_SUCH_FILE_OR_DIR	"No such file or directory"

/*
** ft_perror.c
*/
int			ft_perror(const char *error, const char *suffix);
void		*ft_perrorn(const char *error, const char *suffix);
int			ft_perror_fd(int fd, const char *error, const char *suffix);
void		*ft_perrorn_fd(int fd, const char *error, const char *suffix);
int			ft_perror2(const char *error, const char *prefix, const char *suffix);
void		*ft_perror2n(const char *error, const char *prefix, const char *suffix);
int			ft_perror2_fd(int fd, const char *error, const char *prefix, const char *suffix);
void		*ft_perror2n_fd(int fd, const char *error, const char *prefix, const char *suffix);

#endif
