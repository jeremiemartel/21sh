/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:53:37 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/05 17:56:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_token		*t_token_new(t_test_token_id token_id, int token_union, t_token_type token_type)
{
	t_token		*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->token_type = token_type;
	new->token_id = token_id;
	new->token_union.ival = token_union;
	return (new);
}

void		t_token_debog_show(t_token *token)
{
	if (token->token_id == OPN_PARENT)
		ft_putchar('(');
	else if (token->token_id == CLS_PARENT)
		ft_putchar(')');
	else if (token->token_id == PLUS)
		ft_putchar('+');
	else if (token->token_id == MULT)
		ft_putchar('*');
	else if (token->token_id == INT)
		ft_putnbr(token->token_union.ival);
	ft_putchar(' ');
	return ;
}

void		t_token_debog_show_list(t_list *tokens)
{
	while (tokens)
	{
		t_token_debog_show(tokens->content);
		tokens = tokens->next;
	}
}
