/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 16:32:36 by ldedier          ###   ########.fr       */
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

	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		first_child = (t_ast_node *)node->children->content;
		if (!(heredoc_res = heredoc(context->shell, first_child->token->value,
						heredoc_func, &ret)))
			return (FAILURE);
		//do stuff
		return (SUCCESS);
	}
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
