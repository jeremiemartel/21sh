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

/*
static int	sh_traverse_dgreat_open_file(char *filename)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (stat(filename, &st) != -1)
	{
		if (S_ISDIR(st.st_mode))
			fd = ft_perror(SH_ERR1_IS_DIR, filename);
		else if (access(filename, R_OK))
			fd = ft_perror(SH_ERR1_PERM_DENIED, filename);
	}
	if (fd == FAILURE)
		return (-1);
	if ((fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return (ft_perror("Can't create file", filename));
	return (fd);
}
*/

int		sh_traverse_io_file(t_ast_node *node, t_context *context)
{
//	t_ast_node	*child;
	t_ast_node	*redir_child;
	t_ast_node	*filename_child;
	char		*filename;
//	int			ret;

	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		redir_child = node->children->content;
		filename_child = node->children->next->content;
		filename = filename_child->token->value;

		if (redir_child->symbol->id == sh_index(LEX_TOK_LESS))
		{
//			ret = sh_process_io_file(filename, context);
		}
		else if (redir_child->symbol->id == sh_index(LEX_TOK_DGREAT))
		{

		}	

	}
	return (sh_traverse_tools_browse(node, context));
}
