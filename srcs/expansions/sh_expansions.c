/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/09 17:51:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions(t_context *context, t_ast_node *node)
{
	if (!node || !node->token || !node->token->value)
		return (SUCCESS);
	return (sh_expansion_process(&node->token->value, context));

	// recursilvely find / process expansions
	// field splitting
	// [ Pathname expansion ]
	// Quote removal
}

int				sh_expansion_process(char **input, t_context *context)
{
	return (sh_expansion_process_recursive(input, *input, context));
}

int		sh_expansion_process_recursive(char **input, char *original, t_context *context)
{
	t_expansion	exp;
	int			ret;

	if (!ft_strpbrk(original, "$~`"))
		return (SUCCESS);
	exp.expansion = NULL;
	exp.original = NULL;
	exp.process = NULL;
	exp.res = NULL;
	if (sh_expansions_init(original, &exp) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ERROR);
	}
	if (ft_strpbrk(exp.expansion, "~`$") && !ft_strstr(exp.expansion, "$$"))
	{
		if (sh_expansion_process_recursive(input, exp.expansion, context) == FAILURE)
			return (FAILURE);
		t_expansion_free_content(&exp); //Updating (improve ??)
		if (sh_expansions_init(original, &exp) == FAILURE)
		{
			t_expansion_free_content(&exp);
			return (FAILURE);
		}
	}
	if ((ret = exp.process(context, &exp)) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ret);
	}
	if ((ret = sh_expansions_replace(&exp, input)) != SUCCESS)
	{
		t_expansion_free_content(&exp); /// Leaks all function long
		return (ret);
	}
	t_expansion_free_content(&exp); /// Leaks all function long
	return (SUCCESS);
}

int			sh_expansions_replace(t_expansion *expansion, char **input)
{
	*input = ft_strrep_free(*input, expansion->res->str, expansion->original, 1);
	if (!(*input))
		return (FAILURE);
	return (SUCCESS);
}
