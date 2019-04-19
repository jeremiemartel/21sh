/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_great.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/19 15:44:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_great(t_ast_node *node, t_context *context)
{
	char	*filename;
	int		original_fd;
	int		fd;

	filename = ((t_ast_node*)((t_ast_node*)(node->children->next->content))->children->content)->token->value;
	original_fd = context->father_id;
	if (original_fd < 0)
		original_fd = 1;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (ft_perror("Can't open file", filename));
	if (original_fd <= 2)
		context->fd[original_fd] = fd;
	else
	{
		if ((dup2(fd, original_fd)) == -1)
			return (ft_perror(SH_ERR1_INTERN_ERR, "sh_traverse_great: dup2"));
	}
	return (SUCCESS);
}
