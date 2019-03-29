/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_prod_cmd_prefix(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 1,
		IO_REDIRECT))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CMD_PREFIX,
		IO_REDIRECT))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		LEX_TOK_ASSIGNMENT_WORD))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CMD_PREFIX,
		LEX_TOK_ASSIGNMENT_WORD))
		return (1);
	return (0);
}
