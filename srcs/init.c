/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:19:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 17:45:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_update_shell_lvl(t_shell *shell)
{
	char	*str;
	int		new_lvl;
	char	*new_lvl_str;

	if (!(str = get_env_value((char **)shell->env->tbl, "SHLVL")))
		new_lvl = 1;
	else
		new_lvl = ft_atoi(str) + 1;
	if (!(new_lvl_str = ft_itoa(new_lvl)))
	{
		ft_dy_tab_del(shell->env);
		return (ft_perror(SH_ERR1_MALLOC, "sh_update_shell_lvl"));
	}
	if (sh_add_to_env(shell->env, "SHLVL", new_lvl_str))
	{
		free(new_lvl_str);
		ft_dy_tab_del(shell->env);
		return (ft_perror(SH_ERR1_MALLOC, "sh_update_shell_lvl"));
	}
	free(new_lvl_str);
	return (0);
}

t_dy_tab	*main_init_env(char **env)
{
	int			len;
	int			i;
	t_dy_tab	*tbl;

	len = ft_strtab_len(env);
	if (!(tbl = ft_dy_tab_new(len + 1)))
		return (ft_perrorn(SH_ERR1_MALLOC, "main_init_env"));
	i = 0;
	while (i < len)
	{
		if (ft_dy_tab_add_str(tbl, env[i]))
		{
			ft_dy_tab_del(tbl);
			return (ft_perrorn(SH_ERR1_MALLOC, "main_init_env"));
		}
		i++;
	}
	return (tbl);
}

int		sh_init_shell(t_shell *shell, char **env)
{
	if (!(shell->env = main_init_env(env)))
		return (FAILURE);
	if (!(g_glob.command_line.dy_str = ft_dy_str_new(63)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_init_shell"));
	shell->running = 1;
	if (sh_update_shell_lvl(shell) != SUCCESS)
		return (FAILURE);
	if (sh_init_parsing(&shell->parser) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
