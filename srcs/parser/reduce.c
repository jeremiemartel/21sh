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
//	t_list			*ast_builder_list;
	t_list			*ptr;
	t_ast_builder	*cst_builder;
	t_ast_builder	*ast_builder;

	//ast_builder_list = NULL;
	cst_builder = sh_new_ast_builder_no_token(production->from);
	length = ft_lstlen(production->symbols);

	while (length)
	{
		if (!ft_lstpop_ptr(&parser->stack)) //state
			return (1);
		if (!(ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (1);
		ast_builder = (t_ast_builder *)ptr->content;
		if (ft_lstaddnew_ptr(&cst_builder->node->children, ast_builder->node, sizeof(t_ast_node *)))
			return (1);

	//	if (ast_builder->symbol->relevant && ast_builder->node)
	//	{
		//	if (sh_is_replacing(ast_builder))
		//		replacing_ast_ptr = ptr;
		//	else
	//			ft_lstadd_last(&ast_builder_list, ptr);
	//	}
	//	else
	//	{
	//		if (ast_builder->node)
	//			free(ast_builder->node);
	//		free(ast_builder);
	//		free(ptr);
	//	}
		length--;
	}
//	if (replacing_ast_ptr)
//		parser->root = ((t_ast_builder *)replacing_ast_ptr->content)->node;
	
//	parser->cst_root = cst_builder->node;
//	int i;

//	i = 0;
//	while (ast_builder_list != NULL)
//	{
//		ast_builder = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
//		ft_printf("%d: \n", i++);
//		sh_print_ast_builder(ast_builder);
//		if (ft_lstaddnew_ptr(&((t_ast_builder *)replacing_ast_ptr->
//			content)->node->children, ast_builder->node, sizeof(t_ast_node *)))
//			return (1);
//		if (ft_lstaddnew_ptr(&cst_builder->node->children, ast_builder->node, sizeof(t_ast_node *)))
//			return (1);
//	}
	state_from = (t_state *)parser->stack->content;
	state = parser->lr_tables[state_from->index]
		[production->from->id].action_union.state;
//	if (replacing_ast_ptr == NULL)
//	{
//		if (!(new_ast_builder = sh_new_ast_builder_no_node(production->from)))
//			return (1);
//		if (ft_lstaddnew_ptr(&parser->stack, new_ast_builder, sizeof(t_ast_builder)))
//			return (1);
//	}
//	else
//	{
	//	cst_builder->symbol = production->from;
		if (ft_lstaddnew_ptr(&parser->stack, cst_builder, sizeof(t_ast_builder *)))
			return (1);
	//	ft_lstadd(&parser->stack, sreplacing_ast_ptr);
//	}
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	parser->cst_root = cst_builder->node;
	return (0);
}
