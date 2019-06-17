/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:16:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/17 18:30:38 by ldedier          ###   ########.fr       */
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

int				sh_add_redirection(t_redirection_type type,
					int redirected_fd, int fd, t_list **list)
{
	t_redirection	redirection;
	t_redirection	*found;

	redirection.type = type;
	if (redirected_fd == -1)
	{
		if (type == INPUT)
			redirection.redirected_fd = 0;
		else
			redirection.redirected_fd = 1;
	}
	else
		redirection.redirected_fd = redirected_fd;
	redirection.fd = fd;
	if (!(found = get_redirection(type, redirected_fd, *list)))
	{
		if (ft_lstaddnew_last(list, &redirection, sizeof(t_redirection)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_add_redirection"));
	}
	else
	{
		close(found->fd);
		found->fd = fd;
	}
	return (SUCCESS);
}

int				get_redirected_fd(t_redirection_type type,
					int fd, t_list *redirections)
{
	t_list			*ptr;
	t_redirection	*redir;

	ptr = redirections;
	while (ptr != NULL)
	{
		redir = (t_redirection *)ptr->content;
		if (redir->type == type && redir->redirected_fd == fd)
			return (redir->fd);
		ptr = ptr->next;
	}
	return (fd);
}

int				sh_process_fd_aggregation(t_redirection_type type,
					int redirected_fd, int fd, t_list **redirections)
{
	int new_fd;

	new_fd = get_redirected_fd(type, fd, *redirections);
	return (sh_add_redirection(type, redirected_fd, new_fd, redirections));
}
