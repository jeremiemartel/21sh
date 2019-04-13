/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 12:57:03 by ldedier          ###   ########.fr       */
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
	t_ast_builder	*ast_builder;
	t_ast_builder	*new_ast_builder;

	ast_builder_list = NULL;
	length = ft_lstlen(production->symbols);
	replacing_ast_ptr = NULL;
	while (length)
	{
		if (!ft_lstpop_ptr(&parser->stack)) //state
			return (1);
		if (!(ptr = ft_lstpop_node(&parser->stack))) //ast_builder
			return (1);
		ast_builder = (t_ast_builder *)ptr->content;
		if (ast_builder->symbol->relevant && ast_builder->node)
		{
			if (sh_is_replacing(ast_builder))
				replacing_ast_ptr = ptr;
			else
				ft_lstadd_last(&ast_builder_list, ptr);
		}
		else
		{
			if (ast_builder->node)
				free(ast_builder->node);
			free(ast_builder);
			free(ptr);
		}
		length--;
	}
	if (replacing_ast_ptr)
		parser->root = ((t_ast_builder *)replacing_ast_ptr->content)->node;
	while (ast_builder_list != NULL)
	{
		ast_builder = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr(&((t_ast_builder *)replacing_ast_ptr->
			content)->node->children, ast_builder->node, sizeof(t_ast_node *)))
			return (1);
	}
	state_from = (t_state *)parser->stack->content;
	state = parser->lr_tables[state_from->index]
		[production->from->id].action_union.state;
	if (replacing_ast_ptr == NULL)
	{
		if (!(new_ast_builder = sh_new_ast_builder_no_node(production->from)))
			return (1);
		if (ft_lstaddnew_ptr(&parser->stack, new_ast_builder, sizeof(t_ast_builder)))
			return (1);
	}
	else
	{
		((t_ast_builder *)replacing_ast_ptr->content)->symbol = production->from;
		ft_lstadd(&parser->stack, replacing_ast_ptr);
	}
	if (ft_lstaddnew_ptr(&parser->stack, state, sizeof(t_state *)))
		return (1);
	return (0);
}
