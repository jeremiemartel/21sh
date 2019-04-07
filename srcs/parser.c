/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/03 17:18:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol)
{
	return (symbol->id >= 0 && symbol->id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_test_token_id id,
		int val, t_token_type type)
{
	token->token_union.ival = val;
	token->token_id = id;
	token->token_type = type;
}

int		sh_process_test(void)
{
	t_list	*tokens;
	t_token	token;

	tokens = NULL;  // ((4 + 9) + 5)
	sh_populate_token(&token, OPN_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, OPN_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, INT, 4, TYPE_INT);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, PLUS, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, INT, 9, TYPE_INT);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, CLS_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, PLUS, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, INT, 5, TYPE_INT);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, CLS_PARENT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_populate_token(&token, END_OF_INPUT, 0, TYPE_STR);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	sh_parse_token_list(tokens);
	return (0);
}


