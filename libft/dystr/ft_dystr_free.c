/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dystr_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 09:01:21 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/19 10:30:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_dystr_free:
**		free any t_dystr object
*/

void		ft_dystr_free(t_dystr *dystr)
{
	if (!(dystr))
		return ;
	if (dystr->str)
		free(dystr->str);
	free(dystr);
}
