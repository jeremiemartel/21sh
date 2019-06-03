/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:19:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/31 15:19:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_cfg(t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < NB_SYMBOLS)
	{
		ft_lstdel(&cfg->symbols[i].productions, sh_free_production);
		i++;
	}
	ft_lstdel(&cfg->start_symbol.productions, sh_free_production);
}

void	sh_free_parser(t_lr_parser *parser)
{
	int i;

	sh_free_parser_trees(parser);
	ft_lstdel(&parser->stack, sh_free_stack_item_lst);
	if (parser->lr_tables && parser->nb_states != -1)
	{
		i = 0;
		while (i < parser->nb_states)
		{
			free(parser->lr_tables[i]);
			i++;
		}
		free(parser->lr_tables);
	}
	ft_lstdel(&parser->tokens, sh_free_token_lst);
	sh_free_cfg(&parser->cfg);
}
