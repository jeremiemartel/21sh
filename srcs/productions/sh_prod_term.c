/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_term(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 3,
		TERM,
		SEPARATOR,
		AND_OR))
		return (1);
	if (sh_add_prod(symbol, cfg, 1,
		AND_OR))
		return (1);
	return (0);
}
