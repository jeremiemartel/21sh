/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:24:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/28 20:34:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			process_commands(t_list *commands)
{
	t_list		*ptr;
	t_command	*command;

	while (commands)
	{
		command = (t_command *)(ptr->content);
		ptr = ptr->next;
	}
	return (0);
}
