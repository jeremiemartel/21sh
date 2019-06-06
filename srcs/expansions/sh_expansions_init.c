/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:24:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/06 15:26:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_init:
**	Return Value:
**		FAILURE or SUCCESS
*/
int		sh_expansions_init(char *original, t_expansion *exp)
{
	char	*start;

	exp->res = NULL;
	if (!(start = ft_strpbrk(original, "$~`")))
		return (FAILURE);
	if (ft_strnstr(start, "${", 2))
		return (sh_expansions_parameter_fill(exp, start));
	else if (ft_strnstr(start, "$", 1))
		return (sh_expansions_variable_fill(exp, start));
	else if (ft_strnstr(start, "~", 1))
		return (sh_expansions_tilde_fill(exp, start));
	else
		return (FAILURE);
}
