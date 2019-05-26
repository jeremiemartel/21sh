/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:27:03 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 11:47:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_io_redirect:
**	Father of any redirections operations
**	Find for the optionnal fd value, and stock it into father_id
**		this fd can only be between 0 and 9 (POSIX)
**	Then call childrens
**	
*/

int		sh_traverse_io_redirect(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	int			fd;

	child = (t_ast_node*)node->children->content;
	// Looking for the file descriptor to redirect, -1 means default value
	fd = -1;
	if (child->symbol->id == sh_index(LEX_TOK_IO_NUMBER))
	{
		fd = ft_atoi(child->token->value);
		if (fd > 9 || fd < 0)
			return (ft_perror(SH_ERR1_BAD_FD, child->token->value));
		if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
			return (FAILURE);
		child = (t_ast_node*)node->children->content;
	}
	fd = sh_traverse_tools_browse(node, context);
	return (fd);
}
