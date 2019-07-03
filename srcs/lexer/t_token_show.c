/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_show.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:06:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/03 21:32:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	t_token_show_id_4(int i)
{
	if (i == LEX_TOK_AND_IF)
		ft_putstr("AND_IF");
	else if (i == LEX_TOK_QUOTE_BACK)
		ft_putstr("QUOTE_BACK");
	else if (i == LEX_TOK_IO_NUMBER)
		ft_putstr("IO_NUMBER");
	else
		ft_printf(COLOR_RED"Undefined Token (%d)"COLOR_END, i);
}

static void	t_token_show_id_3(int i)
{
	if (i == LEX_TOK_OR_IF)
		ft_putstr("OR_IF");
	else if (i == LEX_TOK_DSEMI)
		ft_putstr("DSEMI");
	else if (i == LEX_TOK_DLESS)
		ft_putstr("DLESS");
	else if (i == LEX_TOK_DGREAT)
		ft_putstr("DGREAT");
	else if (i == LEX_TOK_LESSAND)
		ft_putstr("LESSAND");
	else if (i == LEX_TOK_GREATAND)
		ft_putstr("GREATAND");
	else if (i == LEX_TOK_LESSGREAT)
		ft_putstr("LESSGREAT");
	else if (i == LEX_TOK_DLESSDASH)
		ft_putstr("DLESSDASH");
	else if (i == LEX_TOK_CLOBBER)
		ft_putstr("CLOBBER");
	else if (i == LEX_TOK_WORD)
		ft_printf("%sWORD%s", BLUE, EOC);
	else if (i == LEX_TOK_TOKEN)
		ft_putstr("TOKEN");
	else
		t_token_show_id_4(i);
}

static void	t_token_show_id_2(int i)
{
	if (i == LEX_TOK_QUOTE_SPL)
		ft_putstr("QUOTE_SPL");
	else if (i == LEX_TOK_QUOTE_DBL)
		ft_putstr("QUOTE_DBL");
	else if (i == LEX_TOK_SPACE)
		ft_putstr("SPACE");
	else if (i == LEX_TOK_TAB)
		ft_putstr("");
	else if (i == LEX_TOK_NEWLINE)
		ft_putstr("NEWLINE");
	else if (i == LEX_TOK_STAR)
		ft_putstr("STAR");
	else if (i == LEX_TOK_QUEST)
		ft_putstr("QUEST");
	else if (i == LEX_TOK_HASH)
		ft_putstr("HASH");
	else if (i == LEX_TOK_TILD)
		ft_putstr("TILD");
	else if (i == LEX_TOK_EQUAL)
		ft_putstr("EQUAL");
	else if (i == LEX_TOK_PERCENT)
		ft_putstr("PERCENT");
	else
		t_token_show_id_3(i);
}

void		t_token_show(t_token *token)
{
	t_token_show_id(token->id);
	ft_dprintf(2, ":%s", token->value);
	if (token->quoted)
		ft_dprintf(2, " quoted:%c", token->quoted);
	if (token->expansion)
		ft_dprintf(2, " (expansion)");
}

void		t_token_show_id(int i)
{
	if (i == LEX_TOK_UNKNOWN)
		ft_putstr(COLOR_RED"UNKNOWN"COLOR_END);
	else if (i == LEX_TOK_ASSIGNMENT_WORD)
		ft_printf("%sASSIGMENT WORD%s", CYAN, EOC);
	else if (i == LEX_TOK_PIPE)
		ft_putstr("PIPE");
	else if (i == LEX_TOK_AND)
		ft_putstr("AND");
	else if (i == LEX_TOK_SEMICOL)
		ft_putstr("SEMICOL");
	else if (i == LEX_TOK_LESS)
		ft_putstr("LESS");
	else if (i == LEX_TOK_GREAT)
		ft_putstr("GREAT");
	else if (i == LEX_TOK_OPN_PAR)
		ft_putstr("OPN_PAR");
	else if (i == LEX_TOK_CLS_PAR)
		ft_putstr("CLS_PAR");
	else if (i == LEX_TOK_DOLLAR)
		ft_putstr("DOLLAR");
	else if (i == LEX_TOK_BACK_SLASH)
		ft_putstr("BACK_SLASH");
	else
		t_token_show_id_2(i);
}
