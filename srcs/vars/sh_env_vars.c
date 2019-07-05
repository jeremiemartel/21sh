/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:48:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/04 17:31:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_env_vars_update_question_mark(t_context *context, int res)
{
	char	*str;

	context->shell->ret_value = res >> 8;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> "COLOR_END);
	if (!(str = ft_itoa(context->shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"%s\n"COLOR_END, str);
	res = sh_vars_assign_key_val(context->env, NULL, "?", str);
	free(str);
	return (res);
}

int		sh_env_vars_update_question_mark_shell(t_shell *shell, int res)
{
	char	*str;

	shell->ret_value = res >> 8;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> "COLOR_END);
	if (!(str = ft_itoa(shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"%s\n"COLOR_END, str);
	res = sh_vars_assign_key_val(shell->env, NULL, "?", str);
	free(str);
	return (res);
}

int		is_key_of_entry(char *entry, char *key)
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

char	*get_env_value(char **env, char *str)
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

char	*get_env_entry(char **env, char *str)
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
