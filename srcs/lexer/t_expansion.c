/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:16:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/14 13:30:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_expansion_free
**		free a t_expansion struct.
*/
void		t_expansion_free(t_expansion *expansion)
{
	if (expansion->original)
		free(expansion->original);
	if (expansion->res)
		ft_dystr_free(expansion->res);
}

void		t_expansion_show(t_expansion *exp)
{
	ft_printf("exp : %d\n", exp->type);
	if (exp->res)
		ft_printf("\tres : %s", exp->res->str);
	if (exp->original)
		ft_printf("\toriginal : %s", exp->original);
}
