/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_scan.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:43:08 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/07 09:59:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_expansions_process(
	char **input, char *original, t_context *context, int *index)
{
	t_expansion	exp;
	int			ret;

	if ((ret = sh_expansions_init(original, &exp)) == ERROR)
	{
		*index += ft_strlen(original);
		return (SUCCESS);
	}
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

static void	backslash(char *input, int *index, int quoted)
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

static int	quote_expansion(
	char **input, int *index, char c, t_context *context)
{
	int		ret;

	ft_strdelchar(*input + *index, 0);
	while ((*input)[*index] != c)
	{
		if (c == '"' && (*input)[*index] == '$')
		{
			ret = sh_expansions_process(input, *input + *index, context, index);
			if (ret != SUCCESS)
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

static int	unquote_expansion(char **input, int *index, t_context *context)
{
	int		ret;

	ret = sh_expansions_process(input, *input + *index, context, index);
	return (ret);
}

int			sh_scan_expansions(char **input, int index, t_context *context)
{
	int		ret;

	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index])
		index++;
	if ((*input)[index] == '\0')
		return (SUCCESS);
	if ((*input)[index] == '\'' || (*input)[index] == '"')
	{
		if ((ret = quote_expansion(input, &index, (*input)[index], context)))
			return (ret);
	}
	else if ((*input)[index] == '$')
	{
		if ((ret = unquote_expansion(input, &index, context)) != SUCCESS)
			return (ret);
	}
	else
		backslash(*input, &index, 0);
	return (sh_scan_expansions(input, index, context));
}
