/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_prod_io_redirect(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 1,
		IO_FILE))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		LEX_TOK_IO_NUMBER,
		IO_FILE))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		IO_HERE))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 2,
		LEX_TOK_IO_NUMBER,
		IO_HERE))
		return (1);
	return (0);
}
