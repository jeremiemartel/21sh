/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_prod_function_body(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 1,
		COMPOUND_COMMAND))
		return (1);
	if (sh_add_prod(symbol, cfg, 2,
		COMPOUND_COMMAND,
		REDIRECT_LIST))
		return (1);
	return (0);
}
