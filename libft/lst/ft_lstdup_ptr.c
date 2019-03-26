/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:53:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/26 10:56:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *ft_lstdup_ptr(t_list *lst)
{
	t_list *res;
	t_list *ptr;

	res = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		if (ft_lstaddnew_ptr_last(&res, ptr->content, ptr->content_size))
		{
			ft_lstdel_ptr(&res);
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (res);
}
