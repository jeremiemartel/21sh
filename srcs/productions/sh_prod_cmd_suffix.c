/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_cmd_suffix(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 1,
		IO_REDIRECT))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CMD_SUFFIX,
		IO_REDIRECT))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		LEX_TOK_WORD))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CMD_SUFFIX,
		LEX_TOK_WORD))
		return (1);
	return (0);
}
