/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_clause.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 07:06:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_for_clause(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 3,
		LEX_TOK_FOR,
		NAME,
		DO_GROUP))
		return (1);
	if (sh_add_prod(symbol, cfg, 4,
		LEX_TOK_FOR,
		NAME,
		SEQUENTIAL_SEP,
		DO_GROUP))
		return (1);
	if (sh_add_prod(symbol, cfg, 6,
		LEX_TOK_FOR,
		NAME,
		LINEBREAK,
		IN,
		SEQUENTIAL_SEP,
		DO_GROUP))
		return (1);
	if (sh_add_prod(symbol, cfg, 7,
		LEX_TOK_FOR, NAME, LINEBREAK, IN, WORDLIST, SEQUENTIAL_SEP, DO_GROUP))
		return (1);
	return (0);
}
