/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:43:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 18:43:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_key_len(char *entry)
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

int		sh_add_to_env(t_dy_tab *env, char *key, char *value)
{
	char	*entry;
	size_t	i;

	i = 0;
	while (i < env->current_size)
	{
		if (is_key_of_entry(env->tbl[i], key))
		{
			ft_dy_tab_suppr_index(env, i);
			break ;
		}
		i++;
	}
	if (!(entry = ft_strjoin_3(key, "=", value)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_add_to_env"));
	if (ft_dy_tab_add_ptr(env, entry))
		return (ft_perror(SH_ERR1_MALLOC, "sh_add_to_env"));
	return (SUCCESS);
}

int		is_bad_assignment(char *entry, int *key_len)
{
	int len;

	if ((len = ft_strlen(entry)) < 3)
		return (1);
	if ((*key_len = get_key_len(entry)) <= 0)
		return (1);
	return (SUCCESS);
}

int		sh_process_setenv_equal(char *entry, t_dy_tab *env)
{
	char	*value;
	char	*key;
	int		key_len;

	if (is_bad_assignment(entry, &key_len))
	{
		ft_dprintf(2, "%s: \'%s\' bad assignment\n", SH_NAME, entry);
		return (1);
	}
	if (!(key = ft_strndup(entry, key_len)))
		return (-1);
	if (!(value = ft_strnrest(entry, key_len + 1)))
	{
		free(key);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_setenv_equal"));
	}
	if (sh_add_to_env(env, key, value))
	{
		free(key);
		free(value);
		return (ft_perror(SH_ERR1_MALLOC, "sh_process_setenv_equal"));
	}
	free(key);
	free(value);
	return (SUCCESS);
}
