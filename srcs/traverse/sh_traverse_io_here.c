/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/27 18:40:35 by ldedier          ###   ########.fr       */
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
static int		sh_traverse_io_here_interactive(t_redirection **redirection,
		t_ast_node *node, t_context *context, char *(*heredoc_func)(char *))
{
	t_ast_node		*first_child;
	char			*heredoc_res;
	int				ret;
	int				fds[2];

	first_child = (t_ast_node *)node->children->content;
	if (!(heredoc_res = heredoc(context->shell, first_child->token->value,
					heredoc_func, &ret)))
		return (FAILURE);
	if (pipe(fds))
		return (ft_perror(SH_ERR1_PIPE, "sh_traverse_io_here_end"));
	(*redirection)->type = INPUT;
	(*redirection)->redirected_fd = 0;
	(*redirection)->fd = fds[0];
	print_redirection(*redirection);
	ft_putstr_fd(heredoc_res, fds[1]);
	close(fds[1]); // ?
	return (SUCCESS);
}

int		sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	t_ast_node		*first_child;
	char			*(*heredoc_func)(char *);
	t_redirection	*redirection;

	redirection = &node->metadata.heredoc_metadata.redirection;
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		first_child = node->children->content;
		if (first_child->symbol->id == sh_index(LEX_TOK_DLESSDASH))
			heredoc_func = &heredoc_dash;
		else
			heredoc_func = &heredoc_no_dash;
		return (sh_traverse_io_here_interactive(&redirection,
				node->children->next->content, context, heredoc_func));
	}
	else if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		if (sh_add_redirection(redirection->type,
				redirection->redirected_fd, redirection->fd,
			&context->current_command_node->metadata
				.command_metadata.redirections))
				return (FAILURE);
	}
	return (SUCCESS);
}
