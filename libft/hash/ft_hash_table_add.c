/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:02:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 15:49:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_hash_table_add(t_hash_table *hash_table,
			void *to_add, void *to_hash, unsigned long (*hash_function)(void *))
{
	unsigned long index;

	index = hash_function(to_hash) % hash_table->size;
	if (ft_lstaddnew_ptr(&hash_table->data[index], to_add, sizeof(void *)))
		return (1);
	return (0);
}
