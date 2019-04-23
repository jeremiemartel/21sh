/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:52:33 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/23 12:13:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_builtin		*t_builtin_new(char *name,
					int (*builtin)(t_dy_tab *argv, t_dy_tab *env))
{
	t_builtin		*new;

	if (!name || !builtin)
		return (NULL);
	if (!(new = malloc(sizeof(*new))))
		return (ft_perrorn(SH_ERR1_MALLOC, "t_builtin_new (1)"));
	if (!(new->name = ft_strdup(name)))
	{
		free(new);
		return (ft_perrorn(SH_ERR1_MALLOC, "t_builtin_new (2)"));
	}
	new->builtin = builtin;
	return (new);
}

void			t_builtin_free(t_builtin *built)
{
	free(built->name);
	free(built);
}

void			t_builtin_free_list(t_list *built_lst)
{
	t_list	*next;

	while (built_lst)
	{
		next = built_lst->next;
		t_builtin_free((t_builtin*)built_lst->content);
		free(built_lst);
		built_lst = next;
	}
}
