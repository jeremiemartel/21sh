/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:49:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/23 12:42:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_builtin_init_add_link(t_list **start, char *name, int (*builtin)(t_dy_tab *argv, t_dy_tab *env))
{
	t_builtin	*buff_built;
	t_list		*buff_list;

	if (!(buff_built = t_builtin_new(name, builtin)))
	{
		t_builtin_free_list(*start);
		return (ft_perror(SH_ERR1_MALLOC, "sh_builtin_init_add_link (1)"));
	}
	if (!(buff_list = ft_lstnew(buff_built, sizeof(t_builtin))))
	{
		t_builtin_free(buff_built);
		t_builtin_free_list(*start);
		return (ft_perror(SH_ERR1_MALLOC, "sh_builtin_init_add_link (1)"));
	}
	ft_lstadd_last(start, buff_list);
	return (SUCCESS);
}

t_list		*sh_builtin_init_list(void)
{
	t_list	*start;

	start = NULL;
	if (sh_builtin_init_add_link(&start, "exit", &sh_builtin_exit) == FAILURE)
		return (NULL);
	if (sh_builtin_init_add_link(&start, "pwd", &sh_builtin_pwd) == FAILURE)
		return (NULL);
	if (sh_builtin_init_add_link(&start, "echo", &sh_builtin_echo) == FAILURE)
		return (NULL);
	
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("exit", &ms_builtin_exit), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("cd", &ms_builtin_cd), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("where", &ms_builtin_where), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("chdir", &ms_builtin_cd), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("myenv", &ms_builtin_myenv), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("pwd", &ms_builtin_pwd), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("setenv", &ms_builtin_setenv), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("unsetenv", &ms_builtin_unsetenv), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("env", &ms_builtin_env), sizeof(t_bin)));
	// ft_lstadd_last(&start, ft_lstnew(t_built_new("echo", &ms_builtin_echo), sizeof(t_bin)));
	return (start);
}

