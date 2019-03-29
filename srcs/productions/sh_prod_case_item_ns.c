/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_item_ns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_case_item_ns(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 3,
		PATTERN,
		LEX_TOK_CLS_PAR,
		LINEBREAK))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 3,
		PATTERN,
		LEX_TOK_CLS_PAR,
		COMPOUND_LIST))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 4,
		LEX_TOK_OPN_PAR,
		PATTERN,
		LEX_TOK_CLS_PAR,
		LINEBREAK))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 4,
		LEX_TOK_OPN_PAR,
		PATTERN,
		LEX_TOK_CLS_PAR,
		COMPOUND_LIST))
		return (1);
	return (0);
}
