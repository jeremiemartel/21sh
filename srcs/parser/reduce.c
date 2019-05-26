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

int		sh_process_reduce(t_production *production, t_lr_parser *parser)
{
	int				length;
	t_state			*state;
	t_state			*state_from;
	t_list			*ast_builder_list;
	t_list			*ptr;
	t_ast_builder	*ast_builder_ptr;
	t_ast_builder	*ast_builder;
	t_ast_node		*replacing_ast_node;

	replacing_ast_node = NULL;
	ast_builder_list = NULL;

	ast_builder = sh_new_ast_builder_no_token(production->from);
	parser->cst_root = ast_builder->cst_node;
	length = ft_lstlen(production->symbols);
	while (length)
	{
		if (!ft_lstpop_ptr(&parser->stack)) //state
			return (1);
		if (!(ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (1);
		ast_builder_ptr = (t_ast_builder *)ptr->content;
		if (ft_lstaddnew_ptr(&parser->cst_root->children, ast_builder_ptr->cst_node, sizeof(t_ast_node *)))
			return (1);
		if (ast_builder_ptr->symbol->relevant && ast_builder_ptr->ast_node)
		{
			if (sh_is_replacing(ast_builder_ptr) && ast_builder_ptr->symbol == production->from && !replacing_ast_node)
				replacing_ast_node = ast_builder_ptr->ast_node;
			else
				ft_lstadd(&ast_builder_list, ptr);
		}
		else
		{
	//		if (ast_builder_ptr->node)
	//			free(ast_builder_ptr->node);
			free(ast_builder_ptr);
			free(ptr);
		}
		length--;
	}
	if (!replacing_ast_node)
	{
		if (!(ast_builder->ast_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
			return (1);
		ast_builder->ast_node->symbol = production->from;
		ast_builder->ast_node->children = NULL;
		ast_builder->ast_node->token = NULL;
	}
	else
		ast_builder->ast_node = replacing_ast_node;
	
	while (ast_builder_list != NULL)
	{
		ast_builder_ptr = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr_last(&ast_builder->ast_node->children, ast_builder_ptr->ast_node, sizeof(t_ast_node *)))
			return (1);
	}
	state_from = (t_state *)parser->stack->content;
	state = parser->lr_tables[state_from->index]
		[production->from->id].action_union.state;
	parser->ast_root = ast_builder->ast_node;
	if (ft_lstaddnew_ptr(&parser->stack, ast_builder, sizeof(t_ast_builder)))
		return (1);
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	return (0);
}
