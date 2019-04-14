/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/14 15:24:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

# define LEX_RULES_LEN	10

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
		ft_perror("Lexer", "Error returned");
	if (lexer.quoted)
		ft_perror("Lexer", "Final result is still quoted");
	lexer_show(&lexer);
	*tokens = lexer.list;
	free(lexer.input);
	if (ret == LEX_END)
		return (SUCCESS);
	return (FAILURE);
	(void)tokens;
}

void	ft_putstr_len(char *str, int len)
{
	write(1, str, len);
}
