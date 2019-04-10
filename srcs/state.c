/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:23:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 15:18:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_state *sh_new_state(void)
{
	t_state		*res;
	static int	index = 0;
	int i;
	int j;
	int k;

	if (!(res = (t_state *)malloc(sizeof(t_state))))
		return (NULL);
	i = 0;
	res->items = NULL;
	while (i < NB_PRODUCTIONS)
	{
		j = 0;
		while (j < NB_TERMS)
		{
			k = 0;
			while (k < NB_SYMBOLS + 1)
				res->items_by_production[i][j][k++] = NULL;
			j++;
		}
		i++;
	}
	res->transitions = NULL;
	res->index = index++;
	ft_printf("%d\n", index);
	return (res);
}

void	sh_free_state(t_state *state)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < NB_PRODUCTIONS)
	{
		j = 0;
		while (j < NB_TERMS)
		{
			k = 0;
			while (k < NB_SYMBOLS + 1)
				ft_lstdel_ptr(&state->items_by_production[i][j][k++]);
			j++;
		}
		i++;
	}
	ft_lstdel_ptr(&state->items);
	ft_lstdel_value(&state->transitions);
	free(state);
	state = NULL;
}
