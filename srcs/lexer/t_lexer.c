/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:39:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 13:21:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	lexer_init(t_lexer *lexer, int tok_start)
{
	lexer->quoted = 0;
	lexer->expansion = 0;
	lexer->tok_start = tok_start;
	lexer->tok_len = 0;
	lexer->current_id = LEX_TOK_UNKNOWN;
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
}

int		lexer_add_token(t_lexer *lexer)
{
	t_list		*new;
	t_token		*token;

	if (lexer->tok_len == 0 && lexer->current_id == LEX_TOK_UNKNOWN)
	{
		lexer_init(lexer, lexer->tok_start + lexer->tok_len);
		return (LEX_OK);
	}
	if (!(token = t_token_new(lexer->current_id, NULL)))
		return (LEX_FAIL);
	if (!(new = ft_lstnew(token, sizeof(token))))
	{
		free(token);
		return (LEX_FAIL);
	}
	ft_lstadd_last(&lexer->list, new);
	if (!(token->value = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len)))
	{
		free(token);
		free(new);
		return (LEX_FAIL);
	}
	token->quoted = ft_abs(lexer->quoted);
	token->expansion = lexer->expansion;
	lexer_init(lexer, lexer->tok_start + lexer->tok_len);
	return (LEX_OK);
}

void	lexer_show(t_lexer *lexer)
{
	t_list	*head;

	head = lexer->list;
	while (head)
	{
		t_token_show((t_token*)head->content);
		if (head->next)
			ft_putstr(" -> ");
		head = head->next;
	}
	ft_putstrn("");
}
