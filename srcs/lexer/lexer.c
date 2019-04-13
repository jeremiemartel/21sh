/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/13 16:31:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

# define DEBUG		0

# define LEX_RULES_LEN	10

int		ft_lstdup(t_list **to, t_list *from)
{
	t_list *ptr;

	*to = NULL;
	ptr = from;
	while (ptr != NULL)
	{
		if (ft_lstaddnew_last(to, ptr->content, ptr->content_size))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int		lexer(char *input, t_list **tokens)
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
	{
		t_lexer_free(&lexer);
		return (LEX_ERR);
	}
	lexer_init(&lexer, 0);
	ft_printf("Starting string :%s\n", lexer.input);
	lexer.list = NULL;
	ret = LEX_CONTINUE;
	while (ret != LEX_ERR && ret != LEX_END)
	{
		i = 0;
		if (DEBUG)
			ft_printf("lexer in progress on : %c\n", lexer.c);
		while ((ret = rules[i](&lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
			i++;
		if (i >= LEX_RULES_LEN)
		{
			ret = LEX_ERR;
			ft_putstrn("No lexer rule applied");
		}
		if (DEBUG)
		{
			ft_printf("rule %d applied\n", i + 1);
			ft_printf("ret : %d\n", ret);
			// ft_printf("new start : %d, new len : %d, new c : %c\n", lexer.tok_start, lexer.tok_len, lexer.c);
		}
		lexer.c = lexer.input[lexer.tok_start + lexer.tok_len];
	}
	if (ret == LEX_ERR)
	{
		ft_putstrn("Error returned by lexer");
		return (1);
	}
	lexer_show(&lexer);	
	if (ft_lstdup(tokens, lexer.list))
		return (LEX_ERR);
	*tokens = lexer.list;
	t_lexer_free(&lexer);
	return (0);
}

void	ft_putstr_len(char *str, int len)
{
	write(1, str, len);
}
