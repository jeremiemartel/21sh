/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/22 15:38:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_ast_node(t_ast_node *ast_node)
{
	free(ast_node);
}

void	sh_free_ast_builder(t_ast_builder *ast_builder)
{
	sh_free_ast_node(ast_builder->ast_node);
	sh_free_ast_node(ast_builder->cst_node);
	free(ast_builder);
}

void	free_file(t_file *file)
{
	free(file->name);
	free(file->fullname);
	free(file);
}

void    free_file_dlst(void *f, size_t dummy)
{
	(void)dummy;
	free_file((t_file *)f);
}

void    free_state_lst(void *s, size_t dummy)
{
	(void)dummy;
	sh_free_state((t_state *)s);
}

void	sh_free_lr_automata(t_lr_parser *parser)
{
	ft_lstdel(&parser->states, free_state_lst);
}

void		sh_free_all(t_shell *shell)
{
	(void)shell;
}
