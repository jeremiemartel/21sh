/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/06 18:34:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
/*
** sh_expansions_init:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure for parameter and variable expansions.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

static int	sh_expansions_init(char *original, t_expansion *exp)
{
	char	*start;

	exp->res = NULL;
	exp->expansion = NULL;
	exp->original = NULL;
	exp->process = NULL;
	exp->res = NULL;
	if (!(start = ft_strpbrk(original, "$")))
		return (ERROR);
	if (ft_strnstr(start, "${", 2))
		return (sh_expansions_parameter_fill(exp, start));
	else if (ft_strnstr(start, "$", 1))
		return (sh_expansions_variable_fill(exp, start));
	else
		return (ERROR);
}

static int			sh_expansions_process(
	char **input, char *original, t_context *context, int *index)
{
	t_expansion	exp;
	int			ret;

	ret = sh_expansions_init(original, &exp);
	if (sh_verbose_expansion())
		t_expansion_show(&exp);
	if (!ret)
		ret = exp.process(context, &exp);
	if (!ret)
		ret = sh_expansions_replace(&exp, input, *index);
	if (ret)
	{
		t_expansion_free_content(&exp);
		return (ret);
	}
	*index += ft_strlen(exp.res->str);
	t_expansion_free_content(&exp);
	return (SUCCESS);
}

static void		backslash(char *input, int *index, int quoted)
{
	if (quoted)
	{
		if (input[*index + 1] == '$' || input[*index + 1] == '"'
			|| input[*index + 1] == '\\')
			ft_strdelchar(input + *index, 0);
	}
	else
		ft_strdelchar(input + *index, 0);
	(*index) += 1;
}

static int 		quote_expansion(char **input, int *index, char c, t_context *context)
{
	int 	ret;

	ft_strdelchar(*input + *index, 0);
	while ((*input)[*index] != c)
	{
		if (c == '"' && (*input)[*index] == '$')
		{
			if ((ret = sh_expansions_process(input, *input + *index, context, index)) != SUCCESS)
				return (ret);
		}
		else if (c == '"' && (*input)[*index] == '\\')
			backslash(*input, index, 1);
		else
			*index += 1;
	}
	ft_strdelchar(*input + *index, 0);
	return (SUCCESS);
}

static int 		unquote_expansion(char **input, int *index, t_context *context)
{
	int 	ret;

	if ((ret = sh_expansions_process(input, *input + *index, context, index)) != SUCCESS)
		return (ret);
	return (SUCCESS);
}

static int 		sh_scan_expansions(char **input, int index, t_context *context)
{
	int 	ret;

	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index])
		index++;
	if ((*input)[index] == '\0')
		return (SUCCESS);
	if ((*input)[index] == '\'' || (*input)[index] == '"')
	{
		if ((ret = quote_expansion(input, &index, (*input)[index], context)) != SUCCESS)
			return (ret);
	}
	else if ((*input)[index] == '$')
	{
		if ((ret = unquote_expansion(input, &index, context)) != SUCCESS)
			return (ret);
	}
	else
	{
		backslash(*input, &index, 0);
	}
	return (sh_scan_expansions(input, index, context));
}

/*
** sh_expansions:
**	Mother function of expansions process. Read the current token in context,
**	and perform various expansions on it. It first detect its category,
**	then perform it, and finally replace original value by result.
**
**	Returned Values:
**		FAILURE : malloc error
**		ERROR : bad expansion detected
**		SUCCESS : expansion successfuly replaced in
**		STOP_CMD_LINE : ${?} or ${?:} expansions
*/

int			sh_expansions(t_context *context, t_ast_node *node)
{
	char	**input;
	int		ret;
	int		index;

	if (!node || !node->token || !node->token->value)
		return (SUCCESS);
	index = 0;
	input = &node->token->value;
	if ((*input)[0] == '~'
		&& (ret = sh_expansions_process_tilde(input, *input, context)) != SUCCESS)
	{
		return (ret);
	}
	ret = sh_scan_expansions(input, index, context);
	if (ret == ERROR || ret == FAILURE)
		sh_env_update_ret_value(context->shell, ret);
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	return (ret);
}

int			sh_expansions_replace(
	t_expansion *expansion, char **input, int index)
{
	*input = ft_strrep_free(
		*input, expansion->res->str, index, ft_strlen(expansion->original));
	if (!(*input))
		return (FAILURE);
	if (sh_verbose_expansion())
	{
		t_expansion_show_type(expansion);
		ft_dprintf(2, " expansion : %s", L_BLUE);
		ft_dprintf(2, "%s => %s\n", expansion->original, expansion->res->str);
		ft_dprintf(2, "new input : %s%s\n", *input, EOC);
	}
	return (SUCCESS);
}
