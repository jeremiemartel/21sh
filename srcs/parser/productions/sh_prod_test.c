/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/30 17:15:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_S(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 2,
		A, B))
		return (1);
//	if (sh_add_prod(symbol, cfg->symbols, 1,
//		B))
//		return (1);
	return (0);
}
int		sh_init_A(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 1,
		T_A))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		EPS))
		return (1);
	return (0);
}

int		sh_init_B(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 2,
		C, C))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		A))
		return (1);
	if (sh_add_prod(symbol, cfg->symbols, 1,
		T_B))
		return (1);
	return (0);
}

int		sh_init_C(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 1, T_C))
		return (1);
	return (0);
}

int		sh_init_D(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg->symbols, 2,
		C, T_C))
		return (1);
	return (0);
}
