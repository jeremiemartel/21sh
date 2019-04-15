/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/15 19:25:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol)
{
	return (symbol->id >= 0 && symbol->id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_symbol_id id,
		int val, t_token_type type)
{
	token->token_union.ival = val;
	token->id = id;
	token->index = sh_index(id);
	token->token_type = type;
}

int		sh_init_context(t_context *context, t_shell *shell)
{
	if (!(context->params = ft_dy_tab_new(5)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_init_context"));
	context->env = shell->env;
	return (SUCCESS);
}

void	sh_free_context(t_context *context)
{
	ft_dy_tab_del(context->params);
}

int		sh_process_traverse(t_lr_parser *parser, t_shell *shell)
{
	t_context	context;

	if (sh_init_context(&context, shell) == FAILURE)
		return (FAILURE);
	g_grammar[parser->ast_root->symbol->id].traverse(parser->ast_root, &context);
	ft_strtab_put((char **)context.params->tbl);
	sh_free_context(&context);
	return (SUCCESS);
}

int	sh_parse_token_list(t_lr_parser *parser, t_shell *shell)
{
	if (sh_lr_parse(parser))
	{
		ft_printf("LEXICAL ERROR\n");
		return (SUCCESS);
	}
	else
	{
		ft_printf("OK !\n");
		ft_printf("\nAST:\n");
		sh_print_ast(parser->ast_root, 0);
//		ft_printf("\n\nCST:\n");
//		sh_print_ast(parser->cst_root, 0);
		return (sh_process_traverse(parser, shell));
	}
}

int		sh_parser(t_list *tokens, t_shell *shell)
{
	t_token token;

	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));

	shell->parser.tokens = tokens;
	return (sh_parse_token_list(&shell->parser, shell));
}
