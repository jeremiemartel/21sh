/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:18:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/10 18:39:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		show_binary(t_binary *binary,
		t_binary_stats *stats, int *empty)
{
	if (*empty == 1)
	{
		ft_printf("%-*s %-*s %-*s\n", stats->max_hits_str_len, "hits",
			stats->max_name_len, "name", stats->max_path_len, "path");
		*empty = 0;
	}
	ft_printf("%4d %-*s %-*s\n", binary->hits,
		stats->max_name_len, binary->name, stats->max_path_len, binary->path);
}

static void		process_builtin_hash_show(t_shell *shell)
{
	t_hash_table	*table;
	unsigned long	i;
	t_list			*ptr;
	int				empty;
	t_binary_stats	stats;

	empty = 1;
	table = shell->binaries;
	update_hash_stats(table, &stats);
	i = 0;
	while (i < table->size)
	{
		ptr = table->data[i];
		while (ptr != NULL)
		{
			show_binary((t_binary *)ptr->content, &stats, &empty);
			ptr = ptr->next;
		}
		i++;
	}
	if (empty)
		ft_printf("hash: hash table empty\n");
}

static void		process_builtin_hash_suppr_all(t_shell *shell)
{
	t_hash_table	*table;
	unsigned long	i;

	table = shell->binaries;
	i = 0;
	while (i < table->size)
	{
		ft_lstdel(&table->data[i], sh_free_binary_lst);
		i++;
	}
}

static int		print_usage(void)
{
	ft_dprintf(2, "21sh: hash: usage: hash [-r]\n");
	return (FAILURE);
}

int				sh_builtin_hash(t_context *context)
{
	if (context->params->current_size == 1)
	{
		process_builtin_hash_show(context->shell);
		return (SUCCESS);
	}
	else if (context->params->current_size == 2)
	{
		if (ft_strcmp(context->params->tbl[1], "-r"))
			return (print_usage());
		else
		{
			process_builtin_hash_suppr_all(context->shell);
			return (SUCCESS);
		}
	}
	else
		return (print_usage());
}
