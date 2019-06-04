/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_tables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:49:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/24 16:35:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_action	**sh_create_tables(t_lr_parser *parser)
{
	t_action	**res;
	int			i;
	int			j;

	parser->nb_states = ft_lstlen(parser->states);
	if (!(res = (t_action **)malloc(parser->nb_states * sizeof(t_action *))))
		return (NULL);
	i = 0;
	while (i < parser->nb_states)
	{
		if (!(res[i] = (t_action *)malloc(NB_SYMBOLS * sizeof(t_action))))
		{
			while (--i)
				free(res[i]);
			free(res);
			return (NULL);
		}
		j = 0;
		while (j < NB_SYMBOLS)
			res[i][j++].action_enum = ERROR;
		i++;
	}
	return (res);
}

int		sh_compute_lr_tables(t_lr_parser *parser)
{
	if (!(parser->lr_tables = sh_create_tables(parser)))
		return (1);
	sh_fill_tables(parser);
	return (0);
}
