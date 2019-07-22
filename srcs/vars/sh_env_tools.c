/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 10:05:51 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/22 11:44:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_env_tools.c :
**	Here are functions to interact with environnement as a (char**) table,
**	only composed by strings using model key=value, where value can be empty.
*/

static int	sh_env_is_key_of_entry(char *entry, char *key)
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

/*
** sh_env_get_value:
**	Look for the value associated to the given key in a char ** tab.
**
**	Returned Values:
**		NULL : key was not found
**		Else : start of then null terminated string containing value.
*/

char		*sh_env_get_value(char **env, char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (sh_env_is_key_of_entry(env[i], str))
			return (&(env[i][len + 1]));
		i++;
	}
	return (NULL);
}
