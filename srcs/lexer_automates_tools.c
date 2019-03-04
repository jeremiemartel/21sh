/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_automates_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:23:50 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/04 18:19:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		sh_lexer_automate_init(t_automate automates[])
{
	int		i;

	i = 0;
	while (i < SH_LEXER_AUTO_LEN)
	{
		automates[i].status = 0;
		i++;
	}
	automates[SPACE].automate = &sh_lexer_auto_space;
	automates[WHILE].automate = &sh_lexer_auto_while;
	automates[GREAT].automate = &sh_lexer_auto_great;
	automates[LESS].automate = &sh_lexer_auto_less;
	automates[WORD].automate = &sh_lexer_auto_word;
	return ;
}

void		sh_lexer_automate_run(t_automate automates[], char c)
{
	int		i;

	i = 0;
	while (i < SH_LEXER_AUTO_LEN)
	{
		automates[i].status = automates[i].automate(automates[i].status, c);
		i++;
	}
	return ;
}

int			sh_lexer_automate_check(t_automate automates[])
{
	int			i;

	i = 0;
	while (i < SH_LEXER_AUTO_LEN)
	{
		if (automates[i].status == end)
			return (i);
		i++;
	}
	return (UNKNOWN);
}

void		sh_lexer_automate_show_status(t_automate automates[], char c)
{
	int			i;

	i = 0;
	ft_printf("%c\t", c);
	while (i < SH_LEXER_AUTO_LEN)
	{
		if (automates[i].status == end)
			ft_printf("%-5s\t", "end");
		else if (automates[i].status == error)
			ft_printf("%-5s\t", "error");
		else
			ft_printf("%- 5d\t", automates[i].status);
		i++;
	}
	ft_putstrn("");
}

void		sh_lexer_show_token(int token)
{
	if (token == UNKNOWN)
		ft_putstrn("unknown");
	else if (token == WHILE)
		ft_putstrn("while");
	else if (token == GREAT)
		ft_putstrn("great");
	else if (token == LESS)
		ft_putstrn("less");
	else if (token == WORD)
		ft_putstrn("word");
}
