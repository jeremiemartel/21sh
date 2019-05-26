/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_great.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 11:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_great:
**	Create a new file, named by the filename symbol
**		(next children of IO_FILE, the father)
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

int			sh_traverse_great(t_ast_node *node, t_context *context)
{
	(void)node;
	(void)context;
	return (SUCCESS);
}
