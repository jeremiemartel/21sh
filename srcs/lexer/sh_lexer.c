/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/23 12:03:47 by jmartel          ###   ########.fr       */
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
	if (!head || ! head->content)
		return (LEX_OK);
	token = (t_token*)head->content;
	// My own rule to detect assignment
	if (ft_strchr(token->value, '=')) //token && token->id == WORD && 
		t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
	while (head)
	{
		token = (t_token*)head->content;
		if (token->id == LEX_TOK_UNKNOWN)
			return (LEX_ERR);
		if (head->next)
			next_token = (t_token*)(head->next->content);
		else
			next_token = NULL;
		if (lexer_is_operator(token->id));
		else if (ft_isdigit_only(token->value) && next_token && (next_token->id == '<' || next_token->id == '>')) // Need to check that there are no blanks between digits and operator
			t_token_update_id(LEX_TOK_IO_NUMBER, token);	
		head = head->next;
	}
	return (LEX_OK);
}


int		sh_lexer(char *input, t_list **tokens, t_shell *shell)
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
	lexer.env = shell->env;
	lexer.vars = shell->vars;
	if (sh_verbose_lexer())
		ft_dprintf(2, "Starting string :%s\n", lexer.input);
	lexer.list = NULL;
	ret = LEX_CONTINUE;
	while (ret != LEX_ERR && ret != LEX_END)
	{
		i = 0;
		if (sh_verbose_lexer())
			ft_printf("lexer in progress on : %c\t", lexer.c);
		while ((ret = rules[i](&lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
			i++;
		if (i >= LEX_RULES_LEN)
			ret = LEX_ERR;
		if (sh_verbose_lexer())
			ft_printf(COLOR_GREEN"\trule %d applied\n"COLOR_END, i + 1);
		lexer.c = lexer.input[lexer.tok_start + lexer.tok_len];
	}
	if (ret == LEX_ERR)
		return (ft_perror("Lexer", "Error returned"));//Leaks
	lexer_lexical_conventions(&lexer);
	// lexer_show(&lexer);
	*tokens = lexer.list;
	free(lexer.input);
	if (ret == LEX_END)
		return (SUCCESS);
	return (FAILURE);
	(void)tokens;
}
