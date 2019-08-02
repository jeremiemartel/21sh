/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/30 20:27:40 by jmartel          ###   ########.fr       */
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

	if (!ft_strchr(original, '$'))
		return (SUCCESS);
	*index = ft_strchr(original, '$') - *input;
	// while (original[*index] != '\'' && original[*index] != '"'
	// 	&& original[*index] != '\\' && original[*index])
	// 	*index += 1;
	if (original)
	ft_printf("on rentre combien de fois\n");
	if (original == '\0')
		return (0);
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

/*
** sh_expansions:
**	Mother function of expansions process. Read the current token in context,
**	and perform various expansions on it. It first detect its category,
**	then perform it, and finally replace original value by result.
**
**	Returned Values:
**		FAILURE : malloc error, see ${?} or ${:?}
**		ERROR : bad expansion detected, see ${?} or ${:?}
**		SUCCESS : expansion successfuly replaced in
*/

int			sh_expansions(t_context *context, t_ast_node *node)
{
	char	**input;
	int		ret;
	int		index;

	ft_printf("ho :%s\n", node->token->value);
	if (!node || !node->token || !node->token->value)
		return (SUCCESS);
	input = &node->token->value;
	if ((ret = sh_expansions_process_tilde(input, *input, context)) != SUCCESS)
	{
		if (sh_env_update_ret_value_and_question(context->shell, ret)
			== FAILURE)
			return (FAILURE);
		return (ret);
	}
	index = 0;
	while (*(*input + index) && ft_strpbrk(*input + index, "$"))
		if ((ret = sh_expansions_process(
			input, *input + index, context, &index)))
			break ;
	if (ret != SUCCESS)
		if (sh_env_update_ret_value_and_question(context->shell, ret))
			return (FAILURE);
	return (ret);
}

int			sh_expansions_replace(
	t_expansion *expansion, char **input, int index)
{
	char	*original;

	original = expansion->original;
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
