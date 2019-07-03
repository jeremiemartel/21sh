/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:04:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/03 21:34:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_symbol(t_symbol *symbol)
{
	if (sh_is_term(symbol))
		ft_dprintf(2, "%s%s%s", BLUE, symbol->debug, EOC);
	else
		ft_dprintf(2, "%s%s%s", RED, symbol->debug, EOC);
}

void	sh_print_token(t_token *token, t_cfg *cfg)
{
	if (token->token_type == TYPE_INT)
		ft_dprintf(2, "%d ", token->token_union.ival);
	else if (token->id == LEX_TOK_WORD)
		ft_dprintf(2, "%s%s %s", YELLOW, token->value, EOC);
	else if (token->id == LEX_TOK_IO_NUMBER)
		ft_dprintf(2, "IO_NUMBER: %s%s %s ", YELLOW, token->value, EOC);
	else
		ft_dprintf(2, "%s%s %s", YELLOW, cfg->symbols[token->index].debug, EOC);
}

void	sh_print_token_list(t_list *list, t_cfg *cfg)
{
	t_list *ptr;

	ptr = list;
	ft_dprintf(2, "token list: ");
	while (ptr != NULL)
	{
		sh_print_token(ptr->content, cfg);
		ptr = ptr->next;
	}
	ft_dprintf(2, "\n\n");
}
