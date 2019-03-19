/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dystr_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 09:11:10 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 09:14:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_dystr_check:
**		Check if with new_offset chars in str, the memory had been enought 
**		allocated. If yes, it returns dystr, else it return
**		result of ft_dystr_realloc function.
*/

t_dystr		*ft_dystr_check(t_dystr *dystr, int new_offset)
{
	if (new_offset + dystr->len <= dystr->size)
		return (dystr);
	return (ft_dystr_realloc(dystr));
}

