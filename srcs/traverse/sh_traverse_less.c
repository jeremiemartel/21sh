/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_less.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/12 15:42:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_less(t_ast_node *node, t_context *context)
{
	char	*filename;
	int		original_fd;
	int		fd;

	filename = ((t_ast_node*)((t_ast_node*)(node->children->next->content))->children->content)->token->value;
	if ((original_fd = context->father_id) < 0)
		original_fd = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ft_perror("'<': ""Can't open", filename));

	// ft_dprintf(2, "traverse : less\n");
	// ft_dprintf(2, "\tfd : %d\n", fd);
	// ft_dprintf(2, "\toriginal_fd : %d\n", original_fd);

	if (original_fd <= 2)
		context->fd[original_fd] = fd;
	else
		if (dup2(fd, original_fd) == -1)
			return (ft_perror(SH_ERR1_ENV_NOT_SET, "sh_traverse_less : dup2"));
	return (SUCCESS);
}
