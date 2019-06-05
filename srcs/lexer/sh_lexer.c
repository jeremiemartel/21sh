/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/05 23:18:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

# define LEX_RULES_LEN	10

/*
** sh_is_name:
**	Check if an assignment is a valid POSIX name variable name is correct
**	In the shell command language, a word consisting solely of underscores,
**	digits, and alphabetics from the portable character set.
**	The first character of a name is not a digit.
**	Loop finish when it met any '=' sign
**
**	return Value : True or False
*/
int		sh_is_name_var_assign(char *name)
{
	int		i;

	if (!ft_isalpha(*name))
		return (0);
	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		lexer_lexical_conventions(t_lexer *lexer) // Is this function steel usefull ??
{
	t_list	*head;
	t_token	*token;
	t_token	*next_token;

	head = lexer->list;
	if (!head || ! head->content)
		return (LEX_OK);
	token = (t_token*)head->content;
	// My own rule to detect assignment
	if (ft_strchr(token->value, '='))
	{
		if (sh_is_name_var_assign(token->value))
			t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
	} 
	while (head)
	{
		token = (t_token*)head->content;
		if (token->id == LEX_TOK_UNKNOWN)
			return (ft_perror("Unknow token detected", "lexer"));
		if (head->next)
			next_token = (t_token*)(head->next->content);
		else
			next_token = NULL;
		head = head->next;
	}
	return (LEX_OK);
}


int		sh_lexer(char *input, t_list **tokens, t_shell *shell)
{
	t_lexer		lexer;
	int			ret;
	int			i;

	lexer.shell = shell;
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
	while (ret != LEX_ERR && ret != LEX_END && ret != LEX_CANCEL)
	{
		i = 0;
		if (sh_verbose_lexer())
			ft_printf("lexer in progress on : %1c\t", lexer.c);
		while ((ret = rules[i](&lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
			i++;
		if (i >= LEX_RULES_LEN)
			ret = LEX_ERR;
		if (sh_verbose_lexer())
			ft_printf(COLOR_GREEN"\trule %d applied\n"COLOR_END, i + 1);
		lexer.c = lexer.input[lexer.tok_start + lexer.tok_len];
	}
	free(lexer.input);
	if (ret == LEX_ERR)
		return (FAILURE);//Leaks
	if (ret == LEX_CANCEL)
		return (LEX_CANCEL); //leaks
	if (lexer_lexical_conventions(&lexer) == LEX_ERR)
		return (LEX_ERR);
	if (sh_verbose_lexer())
		lexer_show(&lexer);
	*tokens = lexer.list;
	if (ret == LEX_END)
		return (SUCCESS);
	return (FAILURE);
}
