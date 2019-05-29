/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/22 15:38:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	free_file(t_file *file)
{
	free(file->name);
	free(file->fullname);
	free(file);
}

void    free_file_dlst(void *f, size_t dummy)
{
	(void)dummy;
	free_file((t_file *)f);
}

/*
void	sh_free_state(t_state *state)
{
	int i;

	ft_lstdel_value(&state->transitions);
	ft_lstdel_value(&state->items);//_by_production[i]);
	i = 0;
	while (i < NB_PRODUCTIONS)
	{
//		ft_lstdel_value(&state->items_by_production[i]);
		i++;
	}
}
*/
void    free_state_lst(void *s, size_t dummy)
{
	(void)dummy;
	sh_free_state((t_state *)s);
}

void	sh_free_lr_automata(t_lr_parser *parser)
{
	ft_lstdel(&parser->states, free_state_lst);
}

void		sh_free_all(t_shell *shell)
{
	(void)shell;
}
