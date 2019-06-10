/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_del_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 12:39:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hash_table_del_value(t_hash_table *table)
{
	unsigned long i;

	i = 0;
	while (i < table->size)
	{
		ft_lstdel_value(&table->data[i]);
		i++;
	}
	free(table);
}
