/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:28:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/01 11:58:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** gnl_join_free : used to join line and the currently readed buffer
**		it's only copy up to the first '/n', or '\0'
**			if param is true, s1 will be freed
**		it return the address of the new malloced string
*/

static char		*gnl_join_free(char *s1, char *s2, int param)
{
	int		len1;
	int		len2;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		res = ft_strdup(s1);
	else
	{
		len1 = ft_strlen(s1);
		len2 = 0;
		while (s2[len2] && s2[len2] != '\n')
			len2++;
		if (!(res = malloc(sizeof(char) * (len1 + len2 + 1))))
			return (NULL);
		if (len1)
			ft_strncpy(res, s1, len1);
		ft_strncpy(res + len1, s2, len2);
		res[len1 + len2] = 0;
	}
	if (param & 0x0001 && s1)
		free(s1);
	return (res);
}

/*
** gnl_read :
**	look if their are datas associated to the fd,
**	else it read on fd and stock it in the linked
**		it join to the line full or part of the
**		buffer
**		Function call herself recursively until
**		it met the end of the line
**	Return values: same as get_next_line
*/

static int		gnl_read(char *gnl, int fd, char **line)
{
	int		ret;

	ret = BUFF_SIZE;
	if (gnl[0] == 0)
	{
		if ((ret = read(fd, gnl, BUFF_SIZE)) == -1)
			return (-1);
		if (ret == 0)
			return (0);
		gnl[ret] = 0;
	}
	*line = gnl_join_free(*line, gnl, 1);
	if (ft_strchr(gnl, '\n'))
	{
		ft_strcpy(gnl, ft_strchr(gnl, '\n') + 1);
		return (1);
	}
	ft_bzero(gnl, BUFF_SIZE + 1);
	if (!**line)
		return (1);
	if (gnl_read(gnl, fd, line) == -1)
		return (-1);
	return (1);
}

/*
**	get_next_line :
**		Read on the fd, and malloc line, to stock the first line
**		It can read on multiple file descriptors at the same time
**		Can cause leaks if you don't read the file until the end
**	Return values:
**		-1 : if any error occured
**		0 : if EOF had been encountered
**		1 : if any line had been read
*/

int				get_next_line(const int fd, char **line)
{
	static char		gnl[GNL_MAX_FD][BUFF_SIZE + 1];
	int				ret;

	if (BUFF_SIZE < 1 || BUFF_SIZE > INT32_MAX)
		return (-1);
	if (fd < 0 || fd >= GNL_MAX_FD || !line)
		return (-1);
	*line = NULL;
	ret = gnl_read(gnl[fd], fd, line);
	return (ret);
}
