/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:36:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/29 18:52:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_stack_item	*new_stack_item(t_ast_builder *ast_builder, int state_index)
{
	t_stack_item *res;

	if (!(res = (t_stack_item *)malloc(sizeof(t_stack_item))))
		return (ft_perrorn(SH_ERR1_MALLOC, "new_stack_item"));
	if (!ast_builder)
	{
		res->stack_enum = E_STACK_STATE_INDEX;
		res->stack_union.state_index = state_index;
	}
	else
	{
		res->stack_enum = E_STACK_AST_BUILDER;
		res->stack_union.ast_builder = ast_builder;
	}
	return (res);
}

int		process_lr_parser_ret(t_lr_parser *parser, t_action action)
{
	if (action.action_enum == SHIFT)
	{
		if (sh_process_shift(action.action_union.state_index, parser))
			return (FAILURE);
	}
	else if (action.action_enum == REDUCE)
	{
		if (sh_process_reduce(action.action_union.production, parser))
			return (FAILURE);
	}
	else if (action.action_enum == ACCEPT)
		return (SUCCESS);
	else if (action.action_enum == ERROR)
		return (2);
	return (3);
}

int		process_lr_parse(t_lr_parser *parser)
{
	t_action		action;
	t_stack_item	*stack_item;
	t_token			*token;
	int				state_index;

	if (parser->stack == NULL)
		return (2);
	stack_item = (t_stack_item *)parser->stack->content;
	if (stack_item->stack_enum != E_STACK_STATE_INDEX)
		return (2);
	else
		state_index = stack_item->stack_union.state_index;
	token = (t_token *)parser->tokens->content;
	action = parser->lr_tables[state_index][token->index];
	return (process_lr_parser_ret(parser, action));
}

/*
**		return values:
**
** 2		-> syntax error
** FAILURE	-> malloc error
*/
int		sh_lr_parse(t_lr_parser *parser)
{
	t_stack_item	*stack_item;
	int				ret;

	ft_lstdel(&parser->stack, sh_free_stack_item_lst);
	if (!(stack_item = new_stack_item(NULL, 0)))
		return (FAILURE);
	if (ft_lstaddnew_ptr(&parser->stack, stack_item, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item);
		return (ft_perror(SH_ERR1_MALLOC, "sh_lr_parse"));
	}
	while (parser->tokens)
	{
		ret = process_lr_parse(parser);
		if (ret != 3)
			return (ret);
	}
	return (2);
}
