/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/27 16:57:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_add_to_list_child_ast_builder(
		t_ast_builder *child_ast_builder, t_production *production,
			t_ast_node **replacing_ast_node, t_list **ast_builder_list)
{
	if (sh_is_replacing(child_ast_builder)
			&& child_ast_builder->symbol == production->from
			&& !*replacing_ast_node)
	{
		*replacing_ast_node = child_ast_builder->ast_node;
		free(child_ast_builder);
	}
	else
	{
		if (ft_lstaddnew_ptr(ast_builder_list, child_ast_builder,
			sizeof(t_ast_builder *)))
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	sh_treat_relevance_in_reduce(
		t_ast_builder *child_ast_builder, t_production *production,
		t_ast_node **replacing_ast_node, t_list **ast_builder_list)
{
	if (child_ast_builder->symbol->relevant)
	{
		if (sh_process_add_to_list_child_ast_builder(child_ast_builder,
					production, replacing_ast_node, ast_builder_list))
			return (FAILURE);
	}
	else
	{
		free(child_ast_builder->ast_node);
		free(child_ast_builder);
	}
	return (SUCCESS);
}

static int	sh_process_process_reduce(t_lr_parser *parser,
				t_production *production, t_list **ast_builder_list,
					t_ast_node **replacing_ast_node)
{
	t_stack_item	*stack_item;
	t_ast_builder	*child_ast_builder;

	ft_lstpop(&parser->stack);
	if (!(stack_item = ft_lstpop_ptr(&parser->stack)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
	child_ast_builder = stack_item->stack_union.ast_builder;
	child_ast_builder->cst_node->builder = NULL;
	child_ast_builder->ast_node->builder = NULL;
	if (ft_lstaddnew_ptr(&parser->cst_root->children,
				child_ast_builder->cst_node, sizeof(t_ast_node *)))
	{
		free(stack_item);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
	}
	if (sh_treat_relevance_in_reduce(child_ast_builder,
				production, replacing_ast_node, ast_builder_list))
	{
		free(stack_item);
		return (FAILURE);
	}
	free(stack_item);
	return (SUCCESS);
}

int			sh_process_reduce_pop(t_production *production,
				t_lr_parser *parser, t_list **ast_builder_list,
					t_ast_node **replacing_ast_node)
{
	int				length;

	length = ft_lstlen(production->symbols);
	while (length)
	{
		if (sh_process_process_reduce(parser, production,
				ast_builder_list, replacing_ast_node))
			return (FAILURE);
		length--;
	}
	return (SUCCESS);
}
