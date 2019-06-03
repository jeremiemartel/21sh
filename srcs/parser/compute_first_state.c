/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_first_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:21:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/24 16:26:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		populate_first_state(t_lr_parser *parser, char lookaheads[NB_TERMS], t_state *first_state)
{
	t_item	*first_item;

	if (!(first_item =
			sh_new_item(parser->cfg.start_symbol.productions->content,
				lookaheads)))
	{
		free(first_state);
		return (FAILURE);
	}
	if (ft_lstaddnew_ptr(&first_state->items, first_item, sizeof(t_item *)))
	{
		free(first_state);
		free(first_item);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_state		*sh_compute_first_state(t_lr_parser *parser)
{
	t_state	*first_state;
	char	lookaheads[NB_TERMS];
	int		i;

	i = 0;
	while (i < NB_TERMS)
	{
		lookaheads[i] = 0;
		i++;
	}
	lookaheads[sh_index(END_OF_INPUT)] = 1;
	if (!(first_state = sh_new_state()))
		return (NULL);
	if (populate_first_state(parser, lookaheads, first_state) != SUCCESS)
		return (NULL);
	return (first_state);
}
