/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patoi_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:19:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/27 16:12:34 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_process_patoi_hex(char **str, int *cvalue,
		unsigned int *result, int *end)
{
	if (ft_isdigit(**str))
		*cvalue = **str - '0';
	else if (ft_toupper(**str) >= 'A' && ft_toupper(**str) <= 'F')
		*cvalue = ft_toupper(**str) - 'A' + 10;
	else
		*end = 1;
	if (*end == 0)
	{
		*result = *result * 0x10 + *cvalue;
		(*str)++;
	}
}

unsigned int	ft_patoi_hex(char **str, int *scss)
{
	unsigned int	result;
	int				cvalue;
	int				end;

	result = 0;
	end = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (**str != '0' && *((*str) + 1) != 'x' && scss)
		*scss = 0;
	*str += 2;
	while (!end)
		ft_process_patoi_hex(str, &cvalue, &result, &end);
	if (scss && (**str != ' ' && **str != '\0' && **str != '\n'))
		*scss = 0;
	return (result);
}
