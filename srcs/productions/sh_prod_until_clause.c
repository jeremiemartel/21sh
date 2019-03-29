/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_clause.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_prod_until_clause(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 3,
		LEX_TOK_UNTIL,
		COMPOUND_LIST,
		DO_GROUP))
		return (1);
	return (0);
}
