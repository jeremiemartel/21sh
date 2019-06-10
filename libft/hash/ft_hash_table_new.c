/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:59:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 12:25:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hash_table *ft_hash_table_new(unsigned long size)
{
	t_hash_table *res;

	if (!(res = malloc(sizeof(t_hash_table))))
		return (NULL);
	res->size = size;
	if (!(res->data = (t_list **)malloc(sizeof(t_list *) * size)))
		return (NULL);
	ft_bzero(res->data, sizeof(t_list *) * size);
	return (res);
}
