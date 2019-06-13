/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:23:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 19:23:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		process_builtin_hash_suppr_all(t_shell *shell)
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
