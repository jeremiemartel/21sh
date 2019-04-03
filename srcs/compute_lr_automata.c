/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_automata.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:39:13 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/03 18:22:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_state *sh_new_state(void)
{
	t_state		*res;
	static int	number = 0;

	res = (t_state *)malloc(sizeof(t_state));
	res->transitions = NULL;
	res->number = number++;
	return (res);
}

t_state	*sh_compute_first_state(t_lr_parser *parser)
{
	t_state *first_state;

	(void)parser;
	if (!(first_state = sh_new_state()))
		return (NULL);
	return (first_state);
}

int		sh_compute_lr_automata(t_lr_parser *parser)
{
	t_state *first_state;

	if (!(first_state = sh_compute_first_state(parser)))
		return (1);
	(void)parser;
	return (0);
}
