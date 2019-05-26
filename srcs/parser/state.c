/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:23:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/24 16:23:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_state *sh_new_state(void)
{
	t_state		*res;
	int			i;
	static int	index = 0;

	if (!(res = (t_state *)malloc(sizeof(t_state))))
		return (NULL);
	i = 0;
	res->transitions = NULL;
	res->items = NULL;
	while (i < NB_PRODUCTIONS)
		res->items_by_production[i++] = NULL;
	res->index = index++;
	return (res);
}

void	sh_free_state(t_state *state)
{
	int i;

	i = 0;
	while (i < NB_PRODUCTIONS)
		ft_lstdel_ptr(&state->items_by_production[i]);
	ft_lstdel_ptr(&state->items);
	ft_lstdel_value(&state->transitions);
	free(state);
	state = NULL;
}
