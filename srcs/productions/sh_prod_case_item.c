/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_case_item(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 5,
		PATTERN,
		LEX_TOK_CLS_PAR,
		LINEBREAK,
		LEX_TOK_DSEMI,
		LINEBREAK))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 5,
		PATTERN,
		LEX_TOK_CLS_PAR,
		COMPOUND_LIST,
		LEX_TOK_DSEMI,
		LINEBREAK))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 6,
		LEX_TOK_OPN_PAR,
		PATTERN,
		LEX_TOK_CLS_PAR,
		LINEBREAK,
		LEX_TOK_DSEMI,
		LINEBREAK))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 6,
		LEX_TOK_OPN_PAR,
		PATTERN,
		LEX_TOK_CLS_PAR,
		COMPOUND_LIST,
		LEX_TOK_DSEMI,
		LINEBREAK))
		return (1);
	return (0);
}
