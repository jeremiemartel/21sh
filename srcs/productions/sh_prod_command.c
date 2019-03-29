/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_command(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 1,
		SIMPLE_COMMAND))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		COMPOUND_COMMAND))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		COMPOUND_COMMAND,
		REDIRECT_LIST))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		FUNCTION_DEFINITION))
		return (1);
	return (0);
}
