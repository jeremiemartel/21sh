/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:07:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/02 22:44:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_hash_cmp_str(void *str1, void *str2)
{
	ft_printf("%s , %s\n", str1, str2);
	return (ft_strcmp((char *)str1, (char *)str2));
}

unsigned long	ft_hash_str(void *ptr)
{
	unsigned long	hash;
	int				c;
	char			*str;

	str = (char *)ptr;
	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}
