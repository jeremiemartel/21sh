/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:16:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/07 14:55:39 by jmartel          ###   ########.fr       */
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
	if (expansion->expansion)
		free(expansion->original);
	if (expansion->res)
		ft_dy_str_free(expansion->res);
}

void		t_expansion_show(t_expansion *exp)
{
	ft_printf("exp : ");
	if (exp->type == 1)
		ft_putstrn("variable");
	else if (exp->type == 2)
		ft_putstrn("parameter");
	else if (exp->type == 3)
		ft_putstrn("command");
	else if (exp->type == 4)
		ft_putstrn("arithmetic");
	else if (exp->type == 5)
		ft_putstrn("tilde");
	if (exp->res)
		ft_printf("\tres : %s", exp->res->str);
	if (exp->original)
		ft_printf("\toriginal : %s", exp->original);
	if (exp->expansion)
		ft_printf("\texpansion : %s", exp->expansion);
	ft_putstrn("");
}
