/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_program(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 3,
		LINEBREAK,
		COMPLETE_COMMANDS,
		LINEBREAK))
		return (1);
	if (sh_add_prod(symbol, cfg, 1,
		LINEBREAK))
		return (1);
	return (0);
}
