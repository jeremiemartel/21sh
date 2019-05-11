/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/11 18:22:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	char	*line;
	char	*eof;
	t_ast_node	*child;

	if (sh_traverse_tools_browse_one_child(node, context) == FAILURE)
		return (FAILURE);
	child = (t_ast_node*)node->children->content;
	if (!(eof = ((t_ast_node*)child->children->content)->token->value))
		return (FAILURE);
	if (pipe(context->pipe))
		return ft_perror(SH_ERR1_INTERN_ERR, "sh_traverse_io_here: piping");
	while (get_next_line(1, &line) == 1)
	{
		if (!ft_strcmp(line, eof))
			break ;
		ft_putstr_fd(line, context->pipe[PIPE_IN]);
		free(line);
	}
	context->fd[FD_IN] = context->pipe[PIPE_OUT];
	return (ft_perror("Function not implemented", "here documents"));
	return (sh_traverse_tools_browse(node, context));
	(void)node;
	(void)context;
}
