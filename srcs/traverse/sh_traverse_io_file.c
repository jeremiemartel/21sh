/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/27 17:09:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_file_output(char *filename,
		t_context *context, int options)
{
	struct stat st;
	int			fd;

	fd = 42; //wat
	if (stat(filename, &st) != -1)
	{
		if (S_ISDIR(st.st_mode))
			fd = ft_perror(SH_ERR1_IS_DIR, filename);
		else if (access(filename, R_OK))
			fd = ft_perror(SH_ERR1_PERM_DENIED, filename);
	}
	if (fd == FAILURE)
		return (FAILURE);
	if ((fd = open(filename, options, 0644)) < 0)
		return (ft_perror("Can't create file", filename));
	if (sh_add_redirection(OUTPUT, context->redirected_fd, fd,
		&context->current_command_node->metadata.command_metadata.redirections))
		return (FAILURE);
	return (SUCCESS);
}

static int	sh_process_file_input(char *filename,
		t_context *context, int options)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (access(filename, F_OK))
		fd = ft_perror(SH_ERR2_NO_SUCH_FILE_OR_DIR, filename);
	if (stat(filename, &st) == -1)
		return (FAILURE);
	else if (access(filename, R_OK))
		fd = ft_perror(SH_ERR1_PERM_DENIED, filename);
	if (fd == FAILURE)
		return (FAILURE);
	if ((fd = open(filename, options)) < 0)
		return (ft_perror("Can't open file", filename));
	if (sh_add_redirection(INPUT, context->redirected_fd, fd,
		&context->current_command_node->metadata.command_metadata.redirections))
		return (FAILURE);
	return (SUCCESS);
}

static int	get_fd(char *filename)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (filename[i])
	{
		if (!ft_isdigit(filename[i]))
			return (-1);
		res = res * 10 + filename[i] - '0';
		i++;
	}
	return (res);
}

static int sh_process_file_greatand(char *filename, t_context *context)
{
	int fd;

	if (!ft_strcmp(filename, "-"))
	{
		if (sh_add_redirection(OUTPUT, context->redirected_fd, -1,
			&context->current_command_node->metadata.command_metadata.redirections))
			return (FAILURE);
		return (SUCCESS);
		
	}
	else if ((fd = get_fd(filename)) <= 2 && fd >= 0)
		return (sh_process_fd_aggregation(OUTPUT, context->redirected_fd, fd,
			&context->current_command_node->metadata.command_metadata.redirections));
	else
	{
		if (fd == -1)
			return (sh_process_file_output(filename, context,
				O_WRONLY | O_TRUNC | O_CREAT));
		else
			ft_dprintf(2, "%d bad file descriptor", fd);
		return (SUCCESS);
	}
}

static int sh_process_file_lessand(char *filename, t_context *context)
{
	int fd;

	if (!ft_strcmp(filename, "-"))
	{
		if (sh_add_redirection(OUTPUT, context->redirected_fd, -1,
			&context->current_command_node->metadata.command_metadata.redirections))
			return (FAILURE);
		return (SUCCESS);
		
	}
	else if ((fd = get_fd(filename)) <= 2 && fd >= 0)
		return (sh_process_fd_aggregation(OUTPUT, context->redirected_fd, fd,
			&context->current_command_node->metadata.command_metadata.redirections));
	else
	{
		if (fd == -1)
			ft_dprintf(2, "ambiguous redirect\n", fd);
		else
			ft_dprintf(2, "%d bad file descriptor\n", fd);
		return (SUCCESS);
	}
}

int		sh_traverse_io_file(t_ast_node *node, t_context *context)
{
	t_ast_node	*redir_child;
	t_ast_node	*filename_child;
	char		*filename;
	int			ret;

	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		redir_child = node->children->content;
		filename_child = node->children->next->content;
		filename = ((t_ast_node *)(filename_child->children->content))->token->value;
		ret = 0;
		if (redir_child->symbol->id == sh_index(LEX_TOK_LESS))
			ret = sh_process_file_input(filename, context, O_RDONLY);
		else if (redir_child->symbol->id == sh_index(LEX_TOK_DGREAT)
			|| redir_child->symbol->id == sh_index(LEX_TOK_CLOBBER))
			ret = sh_process_file_output(filename, context,
				O_WRONLY | O_APPEND | O_CREAT);
		else if (redir_child->symbol->id == sh_index(LEX_TOK_GREAT))
			ret = sh_process_file_output(filename, context,
				O_WRONLY | O_TRUNC | O_CREAT);
		else if (redir_child->symbol->id == sh_index(LEX_TOK_GREATAND))
			ret = sh_process_file_greatand(filename, context);
		else if (redir_child->symbol->id == sh_index(LEX_TOK_LESSAND))
			ret = sh_process_file_lessand(filename, context);
		return (ret);
	}
	return (sh_traverse_tools_browse(node, context));
}
