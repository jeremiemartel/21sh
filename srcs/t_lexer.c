/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:39:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/13 14:06:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	lexer_init(t_lexer *lexer, int tok_start, char *input)
{
	lexer->input = input;
	lexer->quoted = LEX_TOK_UNKNOWN;
	lexer->tok_start = tok_start;
	lexer->tok_len = 0;
	lexer->current_id = LEX_TOK_UNKNOWN;
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
}

int		lexer_add_token(t_lexer *lexer)
{
	t_list		*new;
	t_token		*token;

	if (lexer->tok_len == 0)// || lexer->current_id == LEX_TOK_UNKNOWN)
	{
		lexer_init(lexer, lexer->tok_start + lexer->tok_len, lexer->input);
		return (LEX_OK);
	}
	if (!(token = t_token_new(lexer->current_id, NULL)))
		return (LEX_ERR);
	if (!(new = ft_lstnew(token, sizeof(token))))
	{
		free(token);
		return (LEX_ERR);
	}
	ft_lstadd_last(&lexer->list, new);
	ft_strncpy(token->value, lexer->input + lexer->tok_start, lexer->tok_len);
	lexer_init(lexer, lexer->tok_start + lexer->tok_len, lexer->input);
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
