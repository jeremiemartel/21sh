/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_clause.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_if_clause(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 6,
		LEX_TOK_IF,
		COMPOUND_LIST,
		LEX_TOK_THEN,
		COMPOUND_LIST,
		ELSE_PART,
		LEX_TOK_FI))
		return (1);
	if (sh_add_prod(symbol, cfg, 5,
		LEX_TOK_IF,
		COMPOUND_LIST,
		LEX_TOK_THEN,
		COMPOUND_LIST,
		LEX_TOK_FI))
		return (1);
	return (0);
}
