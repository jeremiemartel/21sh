/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/12 19:34:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

# define DEBUG		0

int		lexer(char *input)
{
	t_lexer		lexer;
	int			ret;

	lexer_init(&lexer, 0, input);
	lexer.list = NULL;
	ret = LEX_CONTINUE;
	while (ret != LEX_ERR && ret != LEX_END)//comparison to \0 shall be removed
	{
		if (DEBUG)
			ft_printf("lexer in progress on : %c\n", lexer.c);
		if ((ret = lexer_rule1(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule1\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule2(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule2\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule3(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule3\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule6(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule6\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule7(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule7\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule8(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule8\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule9(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule9\n");
			if (ret == LEX_ERR)
				break ;
		}
		else if ((ret = lexer_rule10(&lexer)) != LEX_CONTINUE)
		{
			if (DEBUG)
				ft_printf("rule10\n");
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
		if (DEBUG)
			ft_printf("new start : %d, new len : %d, new c : %c\n", lexer.tok_start, lexer.tok_len, lexer.c);
	}
	if (ret == LEX_ERR)
		ft_putstrn("Error returned by lexer");
	lexer_show(&lexer);
	return (0);
}
