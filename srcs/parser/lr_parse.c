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

int		sh_process_shift_adds(t_lr_parser *parser,
			t_ast_builder *ast_builder, int state_index)
{
	t_stack_item *stack_item_ast_builder;
	t_stack_item *stack_item_state_index;

	if (!(stack_item_state_index = new_stack_item(NULL, state_index)))
	{
		sh_free_ast_builder(ast_builder);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	if (!(stack_item_ast_builder = new_stack_item(ast_builder, 0)))
	{
		sh_free_ast_builder(ast_builder);
		sh_free_stack_item(stack_item_state_index);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	if (ft_lstaddnew_ptr(&parser->stack,
		stack_item_ast_builder, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item_state_index);
		sh_free_stack_item(stack_item_ast_builder);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	if (ft_lstaddnew_ptr(&parser->stack,
		stack_item_state_index, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item_state_index);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	return (SUCCESS);
}

int		sh_process_shift(int state_index, t_lr_parser *parser)
{
	t_token	*token;
	t_ast_builder	*ast_builder;

	token = ft_lstpop_ptr(&parser->tokens);
	if (!(ast_builder = sh_new_ast_builder(token,
			&parser->cfg.symbols[token->index])))
	{
		t_token_free(token);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_shift"));
	}
	if (sh_process_shift_adds(parser, ast_builder, state_index) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

/*
** 2		-> syntax error
** FAILURE	-> malloc error
*/
int		sh_lr_parse(t_lr_parser *parser)
{
	t_token			*token;
	t_action		action;
	int				state_index;
	int				i;
	t_stack_item	*stack_item;

	i = 0;

//	ft_printf(GREEN"\n");
//	system("leaks 21sh");
//	sleep(1);
//	ft_printf("%d\n", ft_lstlen(parser->stack));
//	sh_print_parser_state(parser);
	ft_lstdel(&parser->stack, sh_free_stack_item_lst);
//	ft_printf(RED"\n");
//	system("leaks 21sh");
//	sleep(1);
	if (!(stack_item = new_stack_item(NULL, 0)))
		return (FAILURE);
	if (ft_lstaddnew_ptr(&parser->stack, stack_item, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item);
		return (ft_perror(SH_ERR1_MALLOC, "sh_lr_parse"));
	}
	while (parser->tokens)
	{
		if (parser->stack == NULL)
			return (2);
		stack_item = (t_stack_item *)parser->stack->content;
		if (stack_item->stack_enum != E_STACK_STATE_INDEX)
			return (2);
		else
			state_index = stack_item->stack_union.state_index;
		token = (t_token *)parser->tokens->content;
		action = parser->lr_tables[state_index][token->index];
		if (action.action_enum == SHIFT)
		{
//			ft_printf("SHIFT\n");
			if (sh_process_shift(action.action_union.state_index, parser))
				return (FAILURE);
		}
		else if (action.action_enum == REDUCE)
		{
//			ft_printf("REDUCE\n");
			if (sh_process_reduce(action.action_union.production, parser))
				return (FAILURE);
	
		}
		else if (action.action_enum == ACCEPT)
		{
		//	t_token_free(token);
		//	free(parser->tokens);
		//	parser->tokens = NULL;
			return (SUCCESS);
		}
		else if (action.action_enum == ERROR)
		{
//			ft_printf("ERROR\n");
			return (2);
		}
//		sh_print_parser_state(parser);
//		sh_print_ast(parser->ast_root, 0);
	}
	return (2);
}
