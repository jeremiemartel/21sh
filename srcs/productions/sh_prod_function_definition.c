/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_definition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_function_definition(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 5,
		FNAME,
		LEX_TOK_OPN_PAR,
		LEX_TOK_CLS_PAR,
		LINEBREAK,
		FUNCTION_BODY))
		return (1);
	return (0);
}
