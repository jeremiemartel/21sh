/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash_stats.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:57:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 21:57:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		update_hash_stats(t_hash_table *table, t_binary_stats *stats)
{
	unsigned long	i;
	t_binary		*binary;
	int				ret;
	t_list			*ptr;

	stats->max_path_len = 0;
	stats->max_name_len = 0;
	stats->max_hits_str_len = 0;
	i = 0;
	while (i < table->size)
	{
		ptr = table->data[i];
		while (ptr != NULL)
		{
			binary = (t_binary *)ptr->content;
			if ((ret = ft_strlen(binary->path)) > stats->max_path_len)
				stats->max_path_len = ret;
			if ((ret = ft_strlen(binary->name)) > stats->max_name_len)
				stats->max_name_len = ret;
			if ((ret = ft_longlen(binary->hits)) > stats->max_hits_str_len)
				stats->max_hits_str_len = ret;
			ptr = ptr->next;
		}
		i++;
	}
}
