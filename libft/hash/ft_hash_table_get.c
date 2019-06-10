/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:10:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 15:25:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_hash_table_get(t_hash_table *hash_table,
			void *content, unsigned long (*hash_function)(void *),
				int (*compare)(void *ptr1, void *ptr2))
{
	unsigned long	index;
	t_list			*ptr;

	index = hash_function(content) % hash_table->size;
	ptr = hash_table->data[index];
	while (ptr != NULL)
	{
		if (!compare(content, ptr->content))
			return (ptr->content);
	}
	return (NULL);
}

t_hash_finder	ft_hash_table_find(t_hash_table *hash_table,
					void *content, unsigned long (*hash_function)(void *),
						int (*compare)(void *ptr1, void *ptr2))
{
	t_hash_finder	finder;
	unsigned long	index;

	finder.found = 0;
	index = hash_function(content) % hash_table->size;
	finder.current = hash_table->data[index];
	finder.list = &hash_table->data[index];
	finder.prev = NULL;
	finder.content = NULL;
	
	while (finder.current != NULL)
	{
		if (!compare(content, finder.current->content))
		{
			finder.found = 1;
			finder.content = finder.current->content;
			return (finder);
		}
		finder.prev = finder.current;
	}
	return (finder);
}
