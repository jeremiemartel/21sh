/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/25 16:04:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_is_var_name:
**	Check if an assignment is a valid POSIX name variable name is correct
**	In the shell command language, a word consisting solely of underscores,
**	digits, and alphabetics from the portable character set.
**	The first character of a name is not a digit.
**	Loop finish when it met any '=' sign
**
**	return Value : True or False
*/

int				sh_is_var_name(char *name)
{
	int		i;

	if (!ft_isalpha(*name) && !(*name == '_'))
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

/*
** Is this function steel usefull ??
*/

int				sh_lexer_lexical_conventions(t_lexer *lexer)
{
	t_list	*head;
	t_token	*token;

	head = lexer->list;
	if (!head || !head->content)
		return (LEX_OK);
	token = (t_token*)head->content;
	while (head && ft_strchr(token->value, '=') && !token->quoted)
	{
		if (sh_is_var_name(token->value))
			t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
		head = head->next;
		if (head)
			token = (t_token*)head->content;
	}
	while (head)
	{
		token = (t_token*)head->content;
		if (token->id == LEX_TOK_UNKNOWN)
			return (sh_perror_err("lexer", "Unknow token detected"));
		head = head->next;
	}
	return (LEX_OK);
}

static int		sh_lexer_run_rules(t_lexer *lexer)
{
	int				ret;
	int				i;
	static int		(*rules[LEX_RULES_LEN]) (t_lexer *) = {
		&sh_lexer_rule1,
		&sh_lexer_rule2,
		&sh_lexer_rule3,
		&sh_lexer_rule4,
		&sh_lexer_rule5,
		&sh_lexer_rule6,
		&sh_lexer_rule7,
		&sh_lexer_rule8,
		&sh_lexer_rule9,
		&sh_lexer_rule10 };

	i = 0;
	ret = LEX_CONTINUE;
	if (sh_verbose_lexer())
		ft_dprintf(2, "lexer in progress on : %1c\t", lexer->c);
	while ((ret = rules[i](lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
		i++;
	if (sh_verbose_lexer())
		ft_dprintf(2, COLOR_GREEN"\trule %d applied\n"COLOR_END, i + 1);
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
	return (ret);
}

int				sh_lexer(char *input, t_list **tokens, t_shell *shell)
{
	t_lexer		lexer;
	int			ret;

	lexer.shell = shell;
	if (!(lexer.input = ft_strdup(input)))
		return (FAILURE);
	t_lexer_init(&lexer, 0);
	lexer.env = shell->env;
	lexer.vars = shell->vars;
	if (sh_verbose_lexer())
		ft_dprintf(2, "Starting string :%s\n", lexer.input);
	lexer.list = NULL;
	ret = LEX_OK;
	while (ret == LEX_OK)
		ret = sh_lexer_run_rules(&lexer);
	free(lexer.input);
	if (ret != LEX_END)
	{
		t_token_free_list(lexer.list);
		return (ret);
	}
	if (sh_lexer_lexical_conventions(&lexer) == LEX_FAIL)
		return (LEX_FAIL);
	if (sh_verbose_lexer())
		t_lexer_show(&lexer);
	*tokens = lexer.list;
	return (SUCCESS);
}
