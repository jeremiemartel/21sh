/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 22:22:46 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 19:49:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			is_key_of_entry(char *entry, char *key)
{
	int i;

	i = 0;
	while (key[i] && entry[i] && key[i] == entry[i])
		i++;
	if (key[i])
		return (0);
	if (entry[i] != '=')
		return (0);
	return (1);
}

char		*get_env_value(char **env, char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (is_key_of_entry(env[i], str))
			return (&(env[i][len + 1]));
		i++;
	}
	return (NULL);
}

char		*get_env_entry(char **env, char *str)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (is_key_of_entry(env[i], str))
			return (env[i]);
		i++;
	}
	return (NULL);
}

int			process_sh_env(t_dy_tab *env)
{
	size_t i;

	i = 0;
	while (i < env->current_size)
	{
		ft_printf("%s\n", env->tbl[i]);
		i++;
	}
	return (1);
}
