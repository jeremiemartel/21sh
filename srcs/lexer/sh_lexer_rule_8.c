/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:45:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/26 06:21:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule8_assignment(t_lexer *lexer)
{
	char	*buff;
	t_token	*tok;
	t_list	*head;

	buff = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len + 1); // protect
	if (sh_expansions_variable_valid_name(buff))
	{
		head = lexer->list;
		while (head)
		{
			tok = (t_token*)head->content;
			if (tok->id != LEX_TOK_ASSIGNMENT_WORD)
			{
				free(buff);
				return (SUCCESS);
			}
			head = head->next;
		}
		lexer->current_id = LEX_TOK_ASSIGNMENT_WORD;
	}
	free(buff);
	return (SUCCESS);
}

int		sh_lexer_rule8(t_lexer *lexer)
{
	if (lexer->current_id == LEX_TOK_WORD || lexer->current_id == LEX_TOK_ASSIGNMENT_WORD)
	{
		if (lexer->c == '=')
			sh_lexer_rule8_assignment(lexer);
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
