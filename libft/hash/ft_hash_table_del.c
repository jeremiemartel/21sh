/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:35:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 12:39:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hash_table_del(t_hash_table *table,
			void (*del_func)(void *, size_t))
{
	unsigned long i;

	i = 0;
	while (i < table->size)
	{
		ft_lstdel(&table->data[i], del_func);
		i++;
	}
	free(table);
}
