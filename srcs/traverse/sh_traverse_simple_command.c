/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/27 18:41:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


int		sh_traverse_sc_no_slash_cmd(t_context *context);
int		sh_traverse_sc_search_in_dir(char *path, DIR *dir, t_context *context);
int		sh_traverse_sc_search_in_path(t_context *context);

int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		context->redirections = &node->metadata.command_metadata.redirections;
		if (sh_traverse_tools_browse(node, context) == FAILURE)
			return (FAILURE);
		if (!context->params->tbl[0])
			return (SUCCESS);
		if (!ft_strchr(context->params->tbl[0], '/'))
			ret = sh_traverse_sc_no_slash_cmd(context);
		else
		{
			if (!(context->path = ft_strdup(context->params->tbl[0])))
				return (ft_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
			ret = sh_process_execute(context);
		}
		// NEED TO IMPLEMENT EXECVE ERRORS TREATMENT
		sh_traverse_tools_reset_params(context);
		return (ret);
	}
	else
		return (sh_traverse_tools_browse(node, context));
}

int		sh_traverse_sc_no_slash_cmd(t_context *context)
{
	if ((context->builtin = sh_builtin_find(context)))
		return (sh_process_execute_builtin(context));
	// undefined behaviour names
	// Fooking for functions
	// Reserved utility
	if (sh_traverse_sc_search_in_path(context) == FAILURE)
		return (FAILURE);
	if (context->path)
		return (sh_process_execute(context));
	else
	{
		ft_perror(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
		sh_env_vars_update_question_mark(context, 127);
		return (FAILURE);
	}
}

int		sh_traverse_sc_search_in_dir(char *path, DIR *dir, t_context *context)
{
	t_dirent	*dirent;

	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(dirent->d_name, context->params->tbl[0]))
		{
			// ADD PERMISSIONS CHECK
			if (!(context->path = ft_strjoin_path(path, dirent->d_name)))
			{
				closedir(dir);
				return (ft_perror(SH_ERR1_MALLOC, "traverse_sc_search_in_dir"));
			}
			closedir(dir);
			return (SUCCESS);
		}
	}
	closedir(dir);
	return (SUCCESS);
}

int		sh_traverse_sc_search_in_path(t_context *context)
{
	char	**split;
	int		i;
	DIR		*dir;

	split = ft_strsplit(sh_vars_get_value(context->env, context->vars, "PATH"), ':');
	if (!(split))
		return (SUCCESS); //// Nedd to protect path get AND malloc in split
	i = 0;
	while (split[i])
	{
		if (!(dir = opendir(split[i])))
		{
			i++;
			continue ;
		}
		if (sh_traverse_sc_search_in_dir(split[i], dir, context) == FAILURE)
			return (FAILURE);
		if (context->path)
			break ;
		i++;
	}
	ft_strtab_free(split);
	return (SUCCESS);
}
