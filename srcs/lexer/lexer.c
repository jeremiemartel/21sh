/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/15 14:27:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

# define LEX_RULES_LEN	10

int		lexer_lexical_conventions(t_lexer *lexer)
{
	t_list	*head;
	t_token	*token;
	t_token	*next_token;

	head = lexer->list;
	while (head)
	{
		token = (t_token*)head->content;
		if (head->next)
			next_token = (t_token*)(head->next->content);
		else
			next_token = NULL;
		//Rule 1
		if (lexer_is_operator(token->id))
			;
		// Rule 2
		else if (ft_isdigit_only(token->value) && next_token && (next_token->id == '<' || next_token->id == '>'))
			t_token_update_id(LEX_TOK_IO_NUMBER, token);
		// Rule 3
//		else
//			t_token_update_id(LEX_TOK_TOKEN, token);
		head = head->next;
	}
	return (LEX_OK);
}


int		lexer(char *input, t_list **tokens, t_dy_tab *env)
{
	t_lexer		lexer;
	int			ret;
	int			i;

	int (*rules[LEX_RULES_LEN]) (t_lexer *) =
	{
		&lexer_rule1,
		&lexer_rule2,
		&lexer_rule3,
		&lexer_rule4,
		&lexer_rule5,
		&lexer_rule6,
		&lexer_rule7,
		&lexer_rule8,
		&lexer_rule9,
		&lexer_rule10,
	};

	if (!(lexer.input = ft_strdup(input)))
		return (FAILURE);
	lexer_init(&lexer, 0);
	lexer.env = env;
	ft_printf("Starting string :%s\n", lexer.input);
	lexer.list = NULL;
	ret = LEX_CONTINUE;
	while (ret != LEX_ERR && ret != LEX_END)
	{
		i = 0;
		if (LEX_DEBUG)
			ft_printf("lexer in progress on : %c\t", lexer.c);
		while ((ret = rules[i](&lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
			i++;
		if (i >= LEX_RULES_LEN)
			ret = LEX_ERR;
		if (LEX_DEBUG)
			ft_printf(COLOR_GREEN"\trule %d applied\n"COLOR_END, i + 1);
		lexer.c = lexer.input[lexer.tok_start + lexer.tok_len];
	}
	if (ret == LEX_ERR)
		return (ft_perror("Lexer", "Error returned"));//Leaks
	if (lexer.quoted)
		return (ft_perror("Lexer", "Final result is still quoted")); // Leaks, need to check this comdition works 
	lexer_lexical_conventions(&lexer);
	lexer_show(&lexer);
	*tokens = lexer.list;
	free(lexer.input);
	if (ret == LEX_END)
		return (SUCCESS);
	return (FAILURE);
	(void)tokens;
}
