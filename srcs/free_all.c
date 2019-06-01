/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/29 19:45:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_token_lst(void *t, size_t dummy)
{
	(void)dummy;
	t_token_free((t_token *)t);
}

void	sh_free_ast_builder(t_ast_builder *ast_builder)
{
	sh_free_ast_node(&ast_builder->ast_node);
	sh_free_ast_node(&ast_builder->cst_node);
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

void		sh_free_all(t_shell *shell)
{
	sh_free_parser(&shell->parser);
	sh_free_command_line(&g_glob.command_line);
	ft_dlstdel_value(&shell->historic.commands);
	ft_dy_tab_del(shell->vars);
	ft_dy_tab_del(shell->env);
}
