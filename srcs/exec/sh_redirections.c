/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:16:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 15:39:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_redirection	*get_redirection(t_redirection_type type,
					int redirected_fd, t_list *list)
{
	t_list			*ptr;
	t_redirection	*redirection;

	ptr = list;
	while (ptr != NULL)
	{
		redirection = ptr->content;
		if (redirection->type == type
				&& redirection->redirected_fd == redirected_fd)
			return (redirection);
		ptr = ptr->next;
	}
	return (NULL);
}

int		sh_add_redirection(t_redirection_type type,
			int redirected_fd, int fd, t_list **list)
{
	t_redirection	redirection;
	t_redirection	*found;

	redirection.type = type;
	redirection.redirected_fd = redirected_fd;
	redirection.fd = fd;
	if (!(found = get_redirection(type, redirected_fd, *list)))
	{
		if (ft_lstaddnew(list, &redirection, sizeof(t_redirection)))
			return (ft_perror(SH_ERR1_MALLOC, "sh_add_redirection"));
	}
	else
	{
		close(found->fd);
		found->fd = fd;
	}
	return (SUCCESS);
}
