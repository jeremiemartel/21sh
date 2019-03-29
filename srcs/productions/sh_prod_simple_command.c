/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_simple_command(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 3,
		CMD_PREFIX,
		CMD_WORD,
		CMD_SUFFIX))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CMD_PREFIX,
		CMD_WORD))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		CMD_PREFIX))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CMD_NAME,
		CMD_SUFFIX))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		CMD_NAME))
		return (1);
	return (0);
}
