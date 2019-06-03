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
	return (ft_strdup(str));
}

static char *heredoc_canonical_mode(char *eof,
		char *(*heredoc_func)(char *), int *ret)
{
	int			gnl_ret;
	t_gnl_info	info;
	char		*res;
	char		*tmp;

	res = NULL;
	*ret = -1;
	if (!(res = ft_strnew(0)))
		return (ft_perrorn(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
	while ((gnl_ret = get_next_line2(0, &info)) == 1)
	{
		if (info.separator != E_SEPARATOR_ZERO)
		{
			if (!(tmp = heredoc_func(info.line)))
				return (ft_free_turn_strs(&res, &info.line,
					ft_perrorn(SH_ERR1_MALLOC, "heredoc_canonical_mode")));
			if (!ft_strcmp(tmp, eof))
			{
				free(info.line);
				free(tmp);
				*ret = SUCCESS;
				return (res);
			}
			free(info.line);
			if (!(res = ft_strjoin_free(res, tmp, 3)))
				return (ft_perrorn(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
			if (!(res = ft_strjoin_free(res, "\n", 1)))
				return (ft_perrorn(SH_ERR1_MALLOC, "heredoc_canonical_mode"));
		}
		else
		{
			free(info.line);
			return (ft_perrorn("Illegal characters received from input",
						"heredoc_canonical_mode"));
		}
	}
	if (gnl_ret == -1)
	{
		*ret = -2;
		free(res);
		return (NULL);
	}
	free(info.line);
	*ret = SUCCESS;
	return (res);
}

static char *get_heredoc(t_context *context, char *eof,
		char *(*heredoc_func)(char *), int *ret)
{
	if (isatty(0))
		return (heredoc(context->shell, eof, heredoc_func, ret));
	else
		return (heredoc_canonical_mode(eof, heredoc_func, ret));
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

	if (!(heredoc_res = get_heredoc(context, first_child->token->value,
			heredoc_func, &ret)))
		return (FAILURE);
	if (pipe(fds))
		return (ft_perror(SH_ERR1_PIPE, "sh_traverse_io_here_end"));
	(*redirection)->type = INPUT;
	(*redirection)->redirected_fd = 0;
	(*redirection)->fd = fds[0];
	ft_putstr_fd(heredoc_res, fds[1]);
	free(heredoc_res);
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
