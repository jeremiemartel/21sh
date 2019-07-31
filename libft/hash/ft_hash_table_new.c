/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:59:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 17:17:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hash_table	*ft_hash_table_new(unsigned long size)
{
	t_hash_table *res;

	if (!(res = malloc(sizeof(t_hash_table))))
		return (NULL);
	if (!(res->data = (t_list **)malloc(sizeof(t_list *) * size)))
	{
		free(res);
		return (NULL);
	}
	res->size = size;
	ft_bzero(res->data, sizeof(t_list *) * size);
	return (res);
}
