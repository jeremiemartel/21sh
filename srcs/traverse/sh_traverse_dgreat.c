/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_dgreat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/14 12:59:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_dgreat:
**	Open file, named by the filename symbol	(next children of dgreat father:
**		IO_FILE), if the file do not exists it is created
**	Value of the file descriptor opened can be given by an IO_NUMBER symbol
**		In that case this value is stocked in context->father_id
**		Else a negative value is stocked (cf io_redirect traverse)
**	The file is created and can erase any existing file (if allowed to)
**	If fd is one of standard fd it is stocked in context->fd,
**		if previous fd is not a standard one it is closed
**		Else original fd is closed, and the new on is stocked
**	Else dup2 is giving asked value to stream
**	Return Values:
**		A valdi fd if everything worked
**		-1 : if any error occured
*/

static int	sh_traverse_dgreat_open_file(char *filename)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (stat(filename, &st) != -1)
	{
		if (S_ISDIR(st.st_mode))
			fd = ft_perror(SH_ERR1_IS_DIR, filename);
		else if (access(filename, R_OK))
			fd = ft_perror(SH_ERR1_PERM_DENIED, filename);
	}
	if (fd == FAILURE)
		return (-1);
	if ((fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return (ft_perror("Can't create file", filename));
	return (fd);
}

int			sh_traverse_dgreat(t_ast_node *node, t_context *context)
{
	char	*filename;
	int		original_fd;
	int		fd;

	filename = ((t_ast_node*)((t_ast_node*)(node->children->next->content))->children->content)->token->value;
	original_fd = context->father_id;
	if (original_fd < 0)
		original_fd = 1;
	if ((fd = sh_traverse_dgreat_open_file(filename)) < 0)
		return (FAILURE);
	if (original_fd <= 2)
	{
		if (context->fd[original_fd] != original_fd)
			close(context->fd[original_fd]);
		context->fd[original_fd] = fd;
		return (SUCCESS);
	}
	else
	{
		if ((dup2(fd, original_fd)) == -1)
		{
			close(fd);
			return (ft_perror(SH_ERR1_INTERN_ERR, "sh_traverse_dgreat: dup2"));
		}
		if (fd != original_fd)
			close(fd);
	}
	return (SUCCESS);
}
