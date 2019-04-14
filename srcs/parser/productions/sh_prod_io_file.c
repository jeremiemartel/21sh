/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_io_file(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_LESS,
		FILENAME))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_LESSAND,
		FILENAME))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_GREAT,
		FILENAME))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_GREATAND,
		FILENAME))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_DGREAT,
		FILENAME))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_LESSGREAT,
		FILENAME))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_CLOBBER,
		FILENAME))
		return (1);
	return (0);
}
