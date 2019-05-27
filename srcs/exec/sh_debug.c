/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:32:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/27 18:34:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_redirection(t_redirection *redirection)
{
	ft_printf("redirected: %d on %d (on %s)\n", redirection->redirected_fd,
			redirection->fd, redirection->type == INPUT ? "INPUT" :"OUTPUT");
}

void	print_redirection_list(t_list *list)
{
	t_list *ptr;

	ptr = list;
	if(!ptr)
		ft_printf("No redirections !\n");
	while (ptr != NULL)
	{
		print_redirection(ptr->content);
		ptr = ptr->next;
	}
}
