/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:16:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 16:23:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_expansion_free_content
**		free a t_expansion struct.
*/

void		t_expansion_free_content(t_expansion *expansion)
{
	if (expansion->original)
		free(expansion->original);
	if (expansion->expansion)
		free(expansion->expansion);
	if (expansion->res)
		ft_dy_str_free(&expansion->res);
}

/*
** t_expansion_show
**	show res, original and expansion fields of a t_expansion structure
*/

void		t_expansion_show(t_expansion *exp)
{
	ft_printf("exp : ");
	if (exp->res)
		ft_printf("\tres : >>%s<<", exp->res->str);
	if (exp->original)
		ft_printf("\toriginal : >>%s<<", exp->original);
	if (exp->expansion)
		ft_printf("\texpansion : >>%s<<", exp->expansion);
	ft_putstrn("");
}

/*
** t_expansion_show_type
**	show litteral value of type field of a t_expansion structure
*/

void		t_expansion_show_type(t_expansion *exp)
{
	if (exp->type == 1)
		ft_dprintf(2, "variable");
	else if (exp->type == 2)
		ft_dprintf(2, "parameter");
	else if (exp->type == 3)
		ft_dprintf(2, "command");
	else if (exp->type == 4)
		ft_dprintf(2, "arithmetic");
	else if (exp->type == 5)
		ft_dprintf(2, "tilde");
}
