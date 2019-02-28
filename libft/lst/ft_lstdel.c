/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:38:06 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/11 19:38:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*buf;

	while (*alst != NULL)
	{
		buf = *alst;
		*alst = (*alst)->next;
		del(buf->content, buf->content_size);
		free(buf);
		buf = NULL;
	}
	ft_memdel((void*)alst);
	return ;
}
