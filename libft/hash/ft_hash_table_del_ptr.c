/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_del_ptr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:40:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 12:40:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hash_table_del_ptr(t_hash_table *table)
{
	unsigned long i;

	i = 0;
	while (i < table->size)
	{
		ft_lstdel_ptr(&table->data[i]);
		i++;
	}
	free(table);
}
