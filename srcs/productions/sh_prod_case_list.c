/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_prod_case_list(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 2,
		CASE_LIST,
		CASE_ITEM))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		CASE_ITEM))
		return (1);
	return (0);
}
