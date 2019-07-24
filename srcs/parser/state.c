/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:23:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/24 16:48:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_state		*sh_new_state(void)
{
	t_state		*res;
	static int	index = 0;

	if (!(res = (t_state *)malloc(sizeof(t_state))))
		return (NULL);
	res->transitions = NULL;
	res->items = NULL;
	res->index = index++;
	return (res);
}

void		sh_free_state(t_state *state)
{
	ft_lstdel_value(&state->items);
	ft_lstdel_value(&state->transitions);
	free(state);
	state = NULL;
}
