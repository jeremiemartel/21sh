/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/04 03:39:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_simple_command:
**	Traverse used to executed any simple command.
**	In EXECUTE phase : It first call any sons to fill context
**	then it looks for a built in or an executable matching the command name.
**	If any were found it executes it.
**
** return  :
**	FAILURE : malloc error
**	ERROR : command not found
**	SUCCESS : no command were given
**	any value returned by a builtin executed or a process launched
*/

int		sh_traverse_simple_command_exec(t_ast_node *node, t_context *context)
{
	int		ret;

	if ((ret = sh_traverse_tools_browse(node, context)))
		return (ret);
	if (!context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_traverse_sc_no_slash_cmd(context);
	else
	{
		if (!(context->path = ft_strdup(context->params->tbl[0])))
			return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
		if (sh_traverse_sc_check_perm(context,
					context->path, context->params->tbl[0]) != SUCCESS)
			ret = ERROR;
		else
			ret = sh_process_execute(context);
	}
	sh_traverse_tools_reset_params(context);
	return (ret);
}

int		sh_traverse_simple_command_no_exec(t_ast_node *node,
			t_context *context)
{
	(void)node;
	sh_process_execute_close_pipes(context);
	sh_env_vars_update_question_mark(context, 256);
	return (SUCCESS);
}

int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{

	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		context->redirections = &node->metadata.command_metadata.redirections;
		if (node->metadata.command_metadata.should_exec)
			return (sh_traverse_simple_command_exec(node, context));
		else
			return (sh_traverse_simple_command_no_exec(node, context));
	}
	return (sh_traverse_tools_browse(node, context));
}

/*
** sh_traverse_sc_no_slash_cmd:
**	Function launching the execution of a process if context->params->tbl[0]
**	do not contain a path (does not contain a '/' character)
**	It try to launch any builtin, then look in $PATH env variable.
**	If any command was found it is launched
**	(Final else return SUCCESS to let cmd || cmd works)
**
** return  :
**	FAILURE : malloc error
**	ERROR : command not found
**	any value returned by a builtin executed or a process launched
*/

int		sh_traverse_sc_no_slash_cmd(t_context *context)
{
	if ((context->builtin = sh_builtin_find(context)))
		return (sh_exec_builtin(context));
	if (sh_traverse_sc_search_in_hash(context) != SUCCESS)
	{
		if (sh_traverse_sc_search_in_path(context) == FAILURE)
			return (FAILURE);
	}
	if (context->path)
		return (sh_process_execute(context));
	else
	{
		sh_perror_err(SH_ERR1_CMD_NOT_FOUND, context->params->tbl[0]);
		sh_env_vars_update_question_mark(context, SH_RET_CMD_NOT_FOUND);
		return (SUCCESS);
	}
}
