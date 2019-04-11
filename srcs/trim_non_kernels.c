/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_non_kernels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:31:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/11 12:31:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_is_kernel(t_item *item)
{
	return (item->production->symbols != item->progress ||
			item->production->index == 0);
}

void		sh_trim_non_kernels_state(t_state *state)
{
	t_list *ptr;
	t_list *prev;
	t_item *item;
	t_list	*tmp;

	prev = NULL;
	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (!sh_is_kernel(item))
		{
			tmp = ptr->next;
			if (!prev)
				state->items = state->items->next;
			else
				prev->next = prev->next->next;
			sh_print_item(item);
			free(item);
			free(ptr);
			ptr = tmp;
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

void		sh_trim_non_kernels(t_lr_parser *parser)
{
	t_list *ptr;
	t_state *state;

	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		sh_trim_non_kernels_state(state);
		ptr = ptr->next;
	}
}
