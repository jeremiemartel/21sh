/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:43:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/17 11:33:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		get_key_len(char *entry)
{
	int i;

	i = 0;
	while (entry[i])
	{
		if (entry[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	is_bad_assignment(char *entry, int *key_len)
{
	int len;

	if ((len = ft_strlen(entry)) < 3)
		return (1);
	if ((*key_len = get_key_len(entry)) <= 0)
		return (1);
	return (0);
}

static int	sh_process_bad_assignment(t_context *context, char *entry)
{
	ft_dprintf(context->fd[FD_ERR], "%s: \'%s\' bad assignment\n",
		SH_NAME, entry);
	return (ERROR);
}

int		sh_process_setenv_equal(char *entry, t_dy_tab *env, t_context *context)
{
	char	*value;
	char	*key;
	int		key_len;

	if (is_bad_assignment(entry, &key_len))
		return (sh_process_bad_assignment(context, entry));
	if (!(key = ft_strndup(entry, key_len)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_setenv_equal (1)"));
	if (!(value = ft_strnrest(entry, key_len + 1)))
	{
		free(key);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_setenv_equal (1)"));
	}
	if (sh_vars_assign_key_val(env, NULL, key, value) == FAILURE)
	{
		free(key);
		free(value);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_setenv_equal (1)"));
	}
	if (!ft_strcmp(key, "PATH"))
		process_builtin_hash_suppr_all(context->shell);
	free(key);
	free(value);
	return (SUCCESS);
}
