/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_clause.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_case_clause(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 7,
		LEX_TOK_CASE,
		LEX_TOK_WORD,
		LINEBREAK,
		IN,
		LINEBREAK,
		CASE_LIST,
		LEX_TOK_ESAC))
		return (1);
	if (sh_add_prod(symbol, cfg, 7,
		LEX_TOK_CASE,
		LEX_TOK_WORD,
		LINEBREAK,
		IN,
		LINEBREAK,
		CASE_LIST_NS,
		LEX_TOK_ESAC))
		return (1);
	if (sh_add_prod(symbol, cfg, 6,
		LEX_TOK_CASE,
		LEX_TOK_WORD,
		LINEBREAK,
		IN,
		LINEBREAK,
		LEX_TOK_ESAC))
		return (1);
	return (0);
}
