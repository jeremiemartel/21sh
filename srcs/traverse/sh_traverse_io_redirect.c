/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:27:03 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/29 05:14:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_io_redirect:
**	Father of any redirections operations
**	Find for the optionnal fd value, and stock it into father_id
**		this fd can only be between 0 and 9 (POSIX)
**	Then call childrens
*/

int		sh_traverse_io_redirect(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	int			ret;

	child = (t_ast_node*)node->children->content;
	context->redirected_fd = -1;
	if (child->symbol->id == sh_index(LEX_TOK_IO_NUMBER))
		context->redirected_fd = ft_atoi(child->token->value);
	ret = sh_traverse_tools_browse(node, context);
	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE"%s : %s : returned value : %s\n"EOC,
		node->symbol->debug, t_phase_name(context->phase), ret_to_str(ret));
	return (ret);
}
