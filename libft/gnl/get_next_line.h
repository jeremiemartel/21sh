/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:10:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/08 12:54:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
**malloc, free
*/
# include <stdlib.h>

/*
**read(2)
*/
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define BUFF_SIZE 16

typedef	struct	s_file_gnl
{
	int		fd;
	int		size;
	char	*b;
	char	*b_s;
	int		l_s;
	int		i;
	void	*next;
}				t_file_gnl;

void			ft_realloc(char **line, t_file_gnl *file);
void			check_lst(t_file_gnl **lst, int fd);
int				ft_read(t_file_gnl *file, char **line);
int				ft_read2(t_file_gnl *file, char **line);
int				get_next_line(const int fd, char **line);

#endif
