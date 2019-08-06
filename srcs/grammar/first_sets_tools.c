/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:34:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:46:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	is_eps_prod(t_production *production)
{
	return (ft_lstlen(production->symbols) == 0);
}

int			has_eps_prod(t_symbol *symbol)
{
	t_list			*ptr;
	t_production	*production;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (is_eps_prod(production))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
