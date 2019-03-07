/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/07 18:43:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	g_operator[] = "|&;<>()";
char	g_quotes[] = "`'\"";

void	lexer_init(t_lexer *lexer, int tok_start, char *input)
{
	lexer->input = input;
	lexer->quoted = LEX_TOK_UNKNOWN;
	lexer->tok_start = tok_start;
	lexer->tok_len = 0;
	lexer->current_id = LEX_TOK_UNKNOWN;
	lexer->list = NULL;
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
}

int		lexer_add_token(t_lexer *lexer)
{
	t_list		*new;
	t_token		*token;

	if (lexer->tok_len == 0 || lexer->current_id == LEX_TOK_UNKNOWN)
	{
		lexer_init(lexer, lexer->tok_start + lexer->tok_len, lexer->input);
		return (LEX_OK);
	}
	if (!(token = malloc(sizeof(*token))))
		return (LEX_ERR);
	if (!(new = ft_lstnew(token, sizeof(token))))
	{
		free(token);
		return (LEX_ERR);
	}
	ft_lstadd_last(&lexer->list, new);
	token->id = lexer->current_id;
	ft_strncpy(token->value, lexer->input + lexer->tok_start, lexer->tok_len);
	lexer_init(lexer, lexer->tok_start + lexer->tok_len, lexer->input);
	ft_printf("Token added\n");
	return (LEX_OK);
}

int		lexer_rule1(t_lexer *lexer)
{
	if (lexer->c == LEX_TOK_NEWLINE || lexer->c == '\0')//
	{
		lexer_add_token(lexer);
		return (LEX_END);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule7(t_lexer *lexer)
{
	if (lexer->c == LEX_TOK_SPACE && lexer->quoted == LEX_TOK_UNKNOWN)
		return (lexer_add_token(lexer));
	return (LEX_CONTINUE);
}

int		lexer_rule8(t_lexer *lexer)
{
	if (lexer->current_id == LEX_TOK_WORD)
	{
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}

int		lexer_rule10(t_lexer *lexer)
{
	lexer->tok_len = 1;
	lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}

void	lexer_show(t_lexer *lexer)
{
	t_list	*head;

	head = lexer->list;
	while (head)
	{
		ft_printf("%s ", ((t_token*)head->content)->value);
		head = head->next;
	}
	ft_putstrn("");
}

int		lexer(char *input)
{
	t_lexer		lexer;
	int			ret;

	lexer_init(&lexer, 0, input);
	ft_putstrn("Lexer initialized");
	ret = LEX_CONTINUE;
	while (ret != LEX_ERR && ret != LEX_END)//comparison to \0 shall be removed
	{
//		ft_printf("lexer in progress on : %c\n", lexer.c);
		if ((ret = lexer_rule1(&lexer)) != LEX_CONTINUE)
		{
			// ft_printf("rule1\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule7(&lexer)) != LEX_CONTINUE)
		{
			// ft_printf("rule7\n");
			lexer.tok_start++;
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule8(&lexer)) != LEX_CONTINUE)
		{
			// ft_printf("rule8\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule10(&lexer)) != LEX_CONTINUE)
		{
			// ft_printf("rule10\n");
			if (ret == LEX_ERR)
				break ;
		}
		else
		{
			ret = LEX_ERR;
			ft_putstrn("No lexer rule applied");
			break ;
		}
		lexer.c = lexer.input[lexer.tok_start + lexer.tok_len];
	}
	lexer_show(&lexer);
	return (0);
}
