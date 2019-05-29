/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/29 19:29:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int sh_process_reduce_pop(t_production *production,
			t_lr_parser *parser, t_list **ast_builder_list, t_ast_node **replacing_ast_node)
{
	int				length;
	t_list			*child_ast_builder_ptr;
	t_ast_builder	*child_ast_builder;

	length = ft_lstlen(production->symbols);	
	while (length)
	{
		ft_lstpop(&parser->stack); // pop state_index
		if (!(child_ast_builder_ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
		child_ast_builder = (t_ast_builder *)child_ast_builder_ptr->content; // child of production
		if (ft_lstaddnew_ptr(&parser->cst_root->children, child_ast_builder->cst_node, sizeof(t_ast_node *)))
			return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
		if (child_ast_builder->symbol->relevant)
		{
			if (sh_is_replacing(child_ast_builder)
					&& child_ast_builder->symbol == production->from &&
						!*replacing_ast_node)
			{
				*replacing_ast_node = child_ast_builder->ast_node;
				free(child_ast_builder);
				free(child_ast_builder_ptr);
			}
			else
				ft_lstadd(ast_builder_list, child_ast_builder_ptr);
		}
		else
		{
			free(child_ast_builder);
			free(child_ast_builder_ptr);
		}
		length--;
	}
	return (0);
}

static int		sh_process_reduce_add_to_stack(t_lr_parser *parser,
			t_production *production, t_ast_builder *ast_builder)
{
	int				state_index;
	int				state_from_index;

	state_from_index = *(int *)parser->stack->content;
	state_index = parser->lr_tables[state_from_index]
		[production->from->id].action_union.state_index;
	parser->ast_root = ast_builder->ast_node;

	if (ft_lstaddnew_ptr(&parser->stack, ast_builder, sizeof(t_ast_builder)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce_add_to_stack"));
	if (ft_lstaddnew(&parser->stack, &state_index, sizeof(int)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce_add_to_stack"));
	return (SUCCESS);
}

int		sh_process_reduce(t_production *production, t_lr_parser *parser)
{
	t_list			*ast_builder_list;
	t_ast_builder	*child_ast_builder;
	t_ast_builder	*ast_builder;
	t_ast_node		*replacing_ast_node;

	replacing_ast_node = NULL;
	ast_builder_list = NULL;
	ast_builder = sh_new_ast_builder_no_token(production->from);
	parser->cst_root = ast_builder->cst_node;

	if (sh_process_reduce_pop(production, parser, &ast_builder_list,
			&replacing_ast_node))
		return (FAILURE);
	if (replacing_ast_node)
	{
		sh_free_ast_node(&ast_builder->ast_node);
		ast_builder->ast_node = replacing_ast_node;
	}
//	ft_printf(GREEN"\n");
//	system("leaks 21sh");
//sleep(1);
	while (ast_builder_list != NULL)
	{
		child_ast_builder = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr_last(&ast_builder->ast_node->children, child_ast_builder->ast_node, sizeof(t_ast_node *)))
			return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce"));
		free(child_ast_builder);
	}
//	ft_printf(RED"\n");
//	system("leaks 21sh");
//	sleep(1);
	if (sh_process_reduce_add_to_stack(parser, production, ast_builder))
		return (FAILURE);
	return (SUCCESS);
}
