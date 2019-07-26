/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/26 22:42:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
	while (*(*input + index) &&  ft_strpbrk(*input + index, "$"))
	{
		if (sh_verbose_expansion())
		{
			ft_dprintf(2, "expansion var detected\n");
			ft_dprintf(2, "index : %d || input : %s\n", index, *input);
		}
		if ((ret = sh_expansions_process(input, *input + index, context, &index)) != SUCCESS)
		{
			if (sh_env_update_ret_value_and_question(context->shell, ret))
				return (FAILURE);
			return (ret);
		}
	}
	return (SUCCESS);
}

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

int			sh_expansions_process(
	char **input, char *original, t_context *context, int *index)
{
	t_expansion	exp;
	int			ret;

	if (!ft_strpbrk(original, "$"))
		return (SUCCESS);
	if (sh_expansions_init(original, &exp) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ERROR);
	}
	if (sh_verbose_expansion())
		t_expansion_show(&exp);
	if ((ret = exp.process(context, &exp)) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ret);
	}
	if ((ret = sh_expansions_replace(&exp, input)) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ret);
	}
	*index += ft_strlen(exp.res->str);
	t_expansion_free_content(&exp);
	return (SUCCESS);
}

// char		*ft_strrep_free(char *s1, char *s2, int start, int len, int param)
// {
// 	char	*res;
// 	int		i1;
// 	int		i2;
// 	int		lenp;
// 	char	*pt;

// 	if (!(pt = ft_strstr(s1, pattern)))
// 		return (NULL);
// 	lenp = (ft_strlen(s1) + ft_strlen(s2) - ft_strlen(pattern) + 1);
// 	if (!(res = malloc(sizeof(*res) * lenp)))
// 		return (NULL);
// 	i1 = -1;
// 	while (s1 + ++i1 != pt)
// 		res[i1] = s1[i1];
// 	i2 = -1;
// 	while (s2[++i2])
// 		res[i1 + i2] = s2[i2];
// 	lenp = ft_strlen(pattern);
// 	i1--;
// 	while (s1[++i1 + lenp])
// 		res[i1 + i2] = s1[i1 + lenp];
// 	res[i1 + i2] = 0;
// 	ft_strrep_free_free(s1, s2, pattern, param);
// 	return (res);
// }

int			sh_expansions_replace(t_expansion *expansion, char **input)
{
	char	*original;

	original = expansion->original;
	*input = ft_strrep_pattern_free(*input, expansion->res->str, original, 1);
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
