/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 12:36:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int sh_process_reduce_pop(t_production *production,
			t_lr_parser *parser, t_list **ast_builder_list, t_ast_node **replacing_ast_node)
{
	int				length;
	t_list			*ptr;
	t_ast_builder	*ast_builder_ptr;

	length = ft_lstlen(production->symbols);	
	while (length)
	{
		ft_lstpop(&parser->stack);
		if (!(ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
		ast_builder_ptr = (t_ast_builder *)ptr->content; // child of production
		if (ft_lstaddnew_ptr(&parser->cst_root->children, ast_builder_ptr->cst_node, sizeof(t_ast_node *)))
			return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
		if (ast_builder_ptr->symbol->relevant && ast_builder_ptr->ast_node)
		{
			if (sh_is_replacing(ast_builder_ptr) && ast_builder_ptr->symbol == production->from && !*replacing_ast_node)
				*replacing_ast_node = ast_builder_ptr->ast_node;
			else
				ft_lstadd(ast_builder_list, ptr);
		}
		else
		{
			sh_free_ast_builder(ast_builder_ptr);
			free(ptr);
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
	t_ast_builder	*ast_builder_ptr;
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
		sh_free_ast_node(ast_builder->ast_node);
		ast_builder->ast_node = replacing_ast_node;
	}
	while (ast_builder_list != NULL)
	{
		ast_builder_ptr = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr_last(&ast_builder->ast_node->children, ast_builder_ptr->ast_node, sizeof(t_ast_node *)))
			return (ft_perror(SH_ERR1_MALLOC, "sh_process_reduce"));
	}
	if (sh_process_reduce_add_to_stack(parser, production, ast_builder))
		return (FAILURE);
	return (SUCCESS);
}
