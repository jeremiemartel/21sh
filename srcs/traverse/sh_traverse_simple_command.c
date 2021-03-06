/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/08 11:21:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_traverse_simple_command_exec(t_context *context, int *ret)
{
	if (!(context->path = ft_strdup(context->params->tbl[0])))
	{
		sh_process_execute_close_pipes(context);
		return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
	}
	if (sh_traverse_sc_check_perm(context,
				context->path, context->params->tbl[0]) != SUCCESS)
		*ret = ERROR;
	else
		*ret = sh_process_execute(context);
	return (SUCCESS);
}

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
**	STOP_CMD_LINE : a builtin askedto stop line execution
**	SUCCESS : no command were given
**	any value returned by a builtin executed or a process launched
*/

int		sh_traverse_simple_command_exec(t_ast_node *node, t_context *context)
{
	int		ret;

	if ((ret = sh_traverse_tools_browse(node, context)))
		return (ret);
	if (sh_verbose_traverse())
		ft_dprintf(2, BLUE"%-15s : %-12s : cmd name: %s\n"EOC,
		node->symbol->debug, t_phase_name(context->phase),
		context->params->tbl[0]);
	if (!context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_traverse_sc_no_slash_cmd(context);
	else if (sh_process_traverse_simple_command_exec(context, &ret) != SUCCESS)
		return (FAILURE);
	if (ret == ERROR)
		sh_process_execute_close_pipes(context);
	sh_traverse_tools_reset_params(context);
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	if (ret == STOP_CMD_LINE)
		return (ret);
	return (ret == FAILURE ? FAILURE : SUCCESS);
}

int		sh_traverse_simple_command_no_exec(t_ast_node *node,
			t_context *context)
{
	(void)node;
	sh_process_execute_close_pipes(context);
	if (sh_env_update_ret_value_and_question(context->shell, 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		sh_traverse_tools_show_traverse_start(node, context);
		context->redirections = &node->metadata.command_metadata.redirections;
		if (context->current_pipe_sequence_node)
			if (sh_env_update_question_mark(context->shell) == FAILURE)
				return (FAILURE);
		if (node->metadata.command_metadata.should_exec)
			ret = sh_traverse_simple_command_exec(node, context);
		else
			ret = sh_traverse_simple_command_no_exec(node, context);
		sh_traverse_tools_show_traverse_ret_value(node, context, ret);
		return (ret);
	}
	else
	{
		/* to remove when tried and aknowledged

		if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		{
			t_ast_node *new_node;
	
			if (!(new_node = sh_add_to_ast_node(node, CMD_SUFFIX, NULL)))
				return (FAILURE);
			if (!(sh_add_to_ast_node(new_node, LEX_TOK_WORD, "-lRa")))
				return (FAILURE);
			sh_print_ast(context->shell->parser.ast_root, 0);
		}
		*/
		return (sh_traverse_tools_browse(node, context));
	}
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
	{
		if (context->current_pipe_sequence_node)
			return (sh_add_to_pipe_sequence(context));
		else
			return (sh_exec_builtin(context));
	}
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
		if (context->current_pipe_sequence_node)
			context->current_pipe_sequence_node
			->metadata.pipe_metadata.last_ret_value = SH_RET_CMD_NOT_FOUND;
		else
			sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
		return (ERROR);
	}
}
