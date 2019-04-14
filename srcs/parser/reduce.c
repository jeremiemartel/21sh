/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 16:29:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_reduce(t_production *production, t_lr_parser *parser)
{
	int				length;
	t_state			*state;
	t_state			*state_from;
	t_list			*ast_builder_list;
	t_list			*replacing_ast_ptr;
	t_list			*ptr;
	t_ast_builder	*cst_builder;
	t_ast_builder	*ast_builder_ptr;
	t_ast_builder	*ast_builder;

	replacing_ast_ptr = NULL;
	ast_builder_list = NULL;

	cst_builder = sh_new_ast_builder_no_token(production->from);
	parser->cst_root = cst_builder->node;

	length = ft_lstlen(production->symbols);
	while (length)
	{
		if (!ft_lstpop_ptr(&parser->stack)) //state
			return (1);
		if (!(ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (1);
		ast_builder_ptr = (t_ast_builder *)ptr->content;
//		if (ft_lstaddnew_ptr(&parser->cst_root->children, ast_builder_ptr->node, sizeof(t_ast_node *)))
//			return (1);
		if (ast_builder_ptr->symbol->relevant && ast_builder_ptr->node)
		{
			if (sh_is_replacing(ast_builder_ptr) && ast_builder_ptr->symbol == production->from  && !replacing_ast_ptr)
				replacing_ast_ptr = ptr;
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

	if (!replacing_ast_ptr)
	{
		ast_builder = sh_new_ast_builder_no_token(production->from);
		parser->ast_root = ast_builder->node;
	}
	else
		parser->ast_root = ((t_ast_builder *)replacing_ast_ptr->content)->node;

	while (ast_builder_list != NULL)
	{
		ast_builder_ptr = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr_last(&parser->ast_root->children, ast_builder_ptr->node, sizeof(t_ast_node *)))
			return (1);
	}
	state_from = (t_state *)parser->stack->content;
	state = parser->lr_tables[state_from->index]
		[production->from->id].action_union.state;

	if (!replacing_ast_ptr)
	{
		if (ft_lstaddnew_ptr(&parser->stack, ast_builder, sizeof(t_ast_builder)))
			return (1);
	}
	else
		ft_lstadd(&parser->stack, replacing_ast_ptr);
//	if (ft_lstaddnew_ptr(&parser->stack, cst_builder, sizeof(t_ast_builder *)))
//		return (1);
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	return (0);
}
