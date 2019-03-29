/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_prod_brace_group(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 3,
		LEX_TOK_LBRACE,
		COMPOUND_LIST,
		LEX_TOK_RBRACE))
		return (1);
	return (0);
}
