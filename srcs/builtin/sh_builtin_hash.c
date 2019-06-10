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

static void		show_binary(t_binary *binary, int *empty)
{
	if (*empty == 1)
	{
		ft_printf("hits\tname\tpath\n");
		*empty = 0;
	}
	ft_printf("%d\t%s\t%s\n", binary->hits, binary->name, binary->path);
}

static void		process_builtin_hash_show(t_shell *shell)
{
	t_hash_table	*table;
	unsigned long	i;
	t_list			*ptr;
	int				empty;

	empty = 1;
	table = shell->binaries;
	i = 0;
	while (i < table->size)
	{
		ptr = table->data[i];
		while (ptr != NULL)
		{
			show_binary((t_binary *)ptr->content, &empty);
			ptr = ptr->next;
		}
		i++;
	}
	if (empty)
		ft_printf("hash table is empty\n");
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
