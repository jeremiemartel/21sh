/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:19:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/10 18:59:12 by ldedier          ###   ########.fr       */
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

static int		sh_main_init_vars(t_shell *shell)
{
	if (!(shell->vars = ft_dy_tab_new(10)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_main_init_vars"));
	return (SUCCESS);
}

int		sh_init_historic(t_historic *historic)
{
	int			fd;
	char		*line;
	int			ret;

	historic->commands = NULL;
	if ((fd = open(HISTORIC_FILE, O_CREAT | O_RDWR, S_IRWXU)) == -1)
	{
		perror("open");
		return (ft_perror(SH_ERR1_HISTORIC, "sh_unit_historic"));
	}
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_add_to_dlist_ptr(&historic->commands, line, sizeof(line)))
			return (ft_perror(SH_ERR1_MALLOC, "sh_init_historic"));
	}
	free(line);
	historic->head_start.next = historic->commands;
	historic->head_start.prev = NULL;
	historic->head = &historic->head_start;
	close(fd);
	return (SUCCESS);
}

int		sh_init_command_line(t_command_line *command_line)
{
	command_line->autocompletion.choices = NULL;
	command_line->autocompletion.head = NULL;
	command_line->autocompletion.active = 0;
	command_line->autocompletion.scrolled_lines = 0;
	command_line->pinned_index = -1;
	command_line->last_char_input = -1;
	command_line->mode = E_MODE_INSERT;
	if (!(command_line->prompt = ft_strdup(PROMPT)))
		return (FAILURE);
	command_line->clipboard = NULL;
	if (!(command_line->dy_str = ft_dy_str_new(63)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_init_command_line"));
	return (SUCCESS);
}

int		sh_init_shell(t_shell *shell, char **env)
{
	if (!(shell->env = main_init_env(env)))
		return (FAILURE);
	if (sh_main_init_vars(shell) == FAILURE)
		return (FAILURE);
	if (sh_init_command_line(&g_glob.command_line) != SUCCESS)
		return (FAILURE);
	shell->running = 1;
	if (sh_update_shell_lvl(shell) != SUCCESS)
		return (FAILURE);
	if (sh_init_parsing(&shell->parser) != SUCCESS)
		return (FAILURE);
	if ((sh_init_historic(&shell->historic)) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
