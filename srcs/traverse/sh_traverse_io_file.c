/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 18:32:11 by ldedier          ###   ########.fr       */
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
	if ((fd = open(filename, options, S_IRUSR | S_IWUSR)) < 0)
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
		else if (redir_child->symbol->id == sh_index(LEX_TOK_DGREAT))
			ret = sh_process_file_output(filename, context,
				O_WRONLY | O_APPEND | O_CREAT);
		else if (redir_child->symbol->id == sh_index(LEX_TOK_GREAT))
			ret = sh_process_file_output(filename, context,
				O_WRONLY | O_TRUNC | O_CREAT);
		return (ret);
	}
	return (sh_traverse_tools_browse(node, context));
}
