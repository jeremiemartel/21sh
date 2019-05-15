/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/13 17:46:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char		*heredoc_dash(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\t')
		i++;
	return (ft_strdup(&str[i]));
}

char		*heredoc_no_dash(char *str)
{
	return (str);
}

/*
** available return for heredoc() : 
**		FAILURE (malloc error)
**		CTRL_D
**		CTRL_C
*/
static int		sh_traverse_io_here_end(t_ast_node *node,
		t_context *context, char *(*heredoc_func)(char *))
{
	t_ast_node	*first_child;
	char		*heredoc_res;
	int			ret;

	first_child = (t_ast_node *)node->children->content;
	if (!(heredoc_res = heredoc(context->shell, first_child->token->value,
		heredoc_func, &ret)))
		return (FAILURE);
	if (pipe(context->pipe))
		return ft_perror(SH_ERR1_INTERN_ERR, "sh_traverse_io_here: piping");
	ft_putstr_fd(heredoc_res, context->pipe[PIPE_IN]);
	context->fd[FD_IN] = context->pipe[PIPE_OUT];
	return (SUCCESS);
}
int		sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	t_ast_node	*first_child;
	char		*(*heredoc_func)(char *);

	first_child = node->children->content;
	if (first_child->symbol->id == sh_index(LEX_TOK_DLESSDASH))
		heredoc_func = &heredoc_dash;
	else
		heredoc_func = &heredoc_no_dash;
	return (sh_traverse_io_here_end(node->children->next->content,
				context, heredoc_func));
}
