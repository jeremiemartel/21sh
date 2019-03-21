/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:40:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/21 15:18:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_replace(t_expansion *expansion, char **input)
{
	*input = ft_strrep_free(*input, expansion->res->str, expansion->original, 1);
	if (!(*input))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
}

void		lexer_expansion_free(t_expansion *expansion)
{
	if (expansion->original)
		free(expansion->original);
	if (expansion->expansion)
		free(expansion->expansion);
	if (expansion->res)
		ft_dystr_free(expansion->res);
}

int			lexer_expansion_recursive_check(t_lexer *lexer, char **input)
{
	return (LEX_EXP_OK);
}

int			lexer_expansion(t_lexer *lexer, char **input)
{
	t_expansion		expansion;
	char			*buffer;

	//First  call to recursive function
	ft_putstrn("\n");
	if (input == &lexer->input)
	{
		if (!(buffer = ft_strdup(lexer->input + lexer->tok_start + lexer->tok_len)))
			return (LEX_EXP_ERR);
	}
	else
		buffer = *input;
	// ft_printf("Initial expansion : %s\n", buffer);
	if (lexer_expansion_detect(buffer, &expansion) == LEX_EXP_ERR)
		return (LEX_EXP_ERR);
	lexer_expansion_recursive_check(lexer, &buffer);
	if (input == &lexer->input)
		free(buffer);
	lexer_expansion_process(lexer, &expansion);
	if (lexer_expansion_replace(&expansion, input) == LEX_EXP_ERR)
		return (LEX_EXP_ERR);
	// ft_printf("expansion processed res : %s\n", expansion.res->str);
	// ft_printf("expansion output : %s\n", *input);
	lexer->tok_len += ft_strlen(expansion.res->str);
	lexer_expansion_free(&expansion);
	return (LEX_EXP_OK);
	(void)input;
	(void)lexer;
}
