/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_automata.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:21:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 11:21:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_compute_state(t_state *state, t_lr_parser *parser)
{
	int ret;
	int changes;

	changes = 0;
	if ((ret = sh_compute_closure(state, parser))) //to opti: don't check all items
	{
		if (ret == -1)
			return (-1);
		changes = 1;
	}
	if ((ret = sh_compute_transitions(state, parser))) //to opti don't check all items
	{
		if (ret == -1)
			return (-1);
		changes = 1;
	}
	return (changes);
}

int		sh_compute_states(t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;
	int		changes;
	int		ret;

	changes = 0;
	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		if ((ret = sh_compute_state(state, parser)))
		{
			if (ret == -1)
				return (-1);
			changes = 1;
		}
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_compute_lr_automata(t_lr_parser *parser)
{
	t_state *first_state;
	int		ret;

	(void)ret;
	if (!(first_state = sh_compute_first_state(parser)))
		return (1);
	if (ft_lstaddnew_ptr(&parser->states, first_state, sizeof(t_state *)))
	{
		sh_free_state(first_state);
		return (1);
	}
	while ((ret = sh_compute_states(parser)) == 1)
		;
	if (ret == -1)
		return (1);
	sh_compute_closure(first_state, parser);
	sh_compute_transitions(first_state, parser);
	return (0);
}
