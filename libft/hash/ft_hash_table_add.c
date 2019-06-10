/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:02:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 12:26:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_hash_table_add(t_hash_table *hash_table,
			void *content, unsigned long (*hash_function)(void *))
{
	unsigned long index;

	index = hash_function(content) % hash_table->size;
	if (ft_lstaddnew_ptr(&hash_table->data[index], content, sizeof(void *)))
		return (1);
	return (0);
}
