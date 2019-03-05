/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:28:07 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/05 21:28:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		t_cfg_show_productions(t_symbol *symbol)
{
	t_list		*prod;
	t_list		*sym;

	prod = symbol->productions;
	while (prod)
	{
		sym = prod->content;
		while (sym && sym->content)
		{
//			ft_printf("%p ", sym->content);
			// ft_putnbrn(((t_symbol*)sym->content)->id);
			t_symbol_show(((t_symbol*)sym->content)->id);
			sym = sym->next;
		}
		prod = prod->next;
	}
	return ;
}


void		t_cfg_show(t_cfg *cfg)
{
	int		i;

	i = NB_TERMS;
	ft_putstrn("");
	while (i < NB_SYMBOLS)
	{
		ft_printf("%s:\n", cfg->symbols[i].value);
		t_cfg_show_productions(&(cfg->symbols[i]));
		i++;
	}
	return ;
}

int			sh_process_test(void)
{
	t_list	*tokens;
	t_cfg	*cfg;

	tokens = NULL;  // ((4 + 9) * 5)
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(OPN_PARENT, 0, TYPE_STR), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(OPN_PARENT, 0, TYPE_STR), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(INT, 4, TYPE_INT), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(PLUS, 0, TYPE_STR), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(INT, 9, TYPE_INT), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(CLS_PARENT, 0, TYPE_STR), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(MULT, 0, TYPE_STR), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(INT, 5, TYPE_INT), sizeof(t_token)));
	ft_lstadd_last(&tokens, ft_lstnew(t_token_new(CLS_PARENT, 0, TYPE_STR), sizeof(t_token)));
	t_token_debog_show_list(tokens);
	cfg = t_cfg_init();
	t_cfg_show(cfg);
	return (0);
}
