/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_less.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 03:26:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_less:
**	Open a file, named by the filename symbol
**		(next children of IO_FILE, the father)
**	Value of the file descriptor opened can be given by an IO_NUMBER symbol
**		In that case this value is stocked in context->father_id
**		Else a negative value is stocked (cf io_redirect traverse)
**	The file is opened with read only rights
**	If fd is one of standard fd it is stocked in context->fd,
**		if previous fd is not a standard one it is closed
**		Else original fd is closed, and the new on is stocked
**	Else dup2 is giving asked value to stream
**	Return Values:
**		SUCESS or FAILURE
*/

int		sh_traverse_less(t_ast_node *node, t_context *context)
{
	return (sh_traverse_tools_browse(node, context));
}
