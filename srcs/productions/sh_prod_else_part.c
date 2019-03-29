/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_else_part(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 4,
		LEX_TOK_ELIF,
		COMPOUND_LIST,
		LEX_TOK_THEN,
		COMPOUND_LIST))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 5,
		LEX_TOK_ELIF,
		COMPOUND_LIST,
		LEX_TOK_THEN,
		COMPOUND_LIST,
		ELSE_PART))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		LEX_TOK_ELSE,
		COMPOUND_LIST))
		return (1);
	return (0);
}
