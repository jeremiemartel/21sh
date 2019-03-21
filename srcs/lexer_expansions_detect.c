/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_detect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:54:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/21 12:31:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_detect(char *input, t_expansion *expansion)
{
	if (*input == '`')
		return (lexer_expansion_detect_command(input, expansion));
	else if (ft_strnstr(input, "$((", 3))
		return (lexer_expansion_detect_arithmetic(input, expansion));
	else if (ft_strnstr(input, "$(", 2))
		return (lexer_expansion_detect_command(input, expansion));
	else if (ft_strnstr(input, "${", 2))
		return (lexer_expansion_detect_parameter(input, expansion));
	else if (ft_strnstr(input, "$", 1))
		return (lexer_expansion_detect_variable(input, expansion));
	else
	{
		ft_putstrn("\033[31mNo expansions detectd in expasion_detect%s\033[0m");
		return (LEX_EXP_ERR);
	}
	return (LEX_EXP_ERR);
}

int			lexer_expansion_detect_command(char *input, t_expansion *expansion)
{
	expansion->type = LEX_EXP_CMD;
	expansion->res = NULL;
	// ft_putstrn("expansion_detect_command : 0");
	if (*input == '`')
	{
		// ft_putstrn("expansion_detect_command : case 1.0");
		expansion->original = ft_strndup(input, ft_strchr(input + 1, '`') - input + 1); //+1 ??
		// ft_putstrn("expansion_detect_command : case 1.1");
		expansion->expansion = ft_strndup(input + 1, ft_strchr(input + 1, '`') - (input + 1));
		// ft_putstrn("expansion_detect_command : case 1.2");
		ft_printf("creating expansion : \n\texpansion : %s\n", expansion->expansion);
	}
	else
	{
		// ft_putstrn("expansion_detect_command : case 2");
		expansion->original = ft_strndup(input, ft_strchr(input + 2, ')') - input + 1); //+1?
		expansion->expansion = ft_strndup(input + 2, ft_strchr(input + 2, ')') - (input + 2));
	}
	if (!expansion->original || !expansion->expansion)
	{
		if (expansion->original)
			free(expansion->original);
		if (expansion->expansion)
			free(expansion->expansion);
		return (LEX_EXP_ERR);
	}
	ft_printf("detecting command : \n\toriginal : %s\n\texpansion: %s\n", expansion->original, expansion->expansion);
	return (LEX_EXP_OK);
}

int			lexer_expansion_detect_arithmetic(char *input, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)expansion;
	(void)input;
}

int			lexer_expansion_detect_parameter(char *input, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)expansion;
	(void)input;
}

int			lexer_expansion_detect_variable(char *input, t_expansion *expansion)
{
	return (LEX_EXP_ERR);
	(void)expansion;
	(void)input;
}
