/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:40:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/11 17:39:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** lexer_expansion:
**		Supposed to recursively process expansions, changing one otken to one
**		or more tokens, following POSIX rules.
*/
int			lexer_expansion(t_lexer *lexer, char **input)
{
	t_expansion		expansion;
	char			*buffer;

	//First  call to recursive function
	ft_putstrn("");
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
	ft_printf("Expansion detected : \n\toriginal : %s\n\texpansion: %s\n", expansion.original, expansion.expansion);
	if (input == &lexer->input)
		free(buffer);
	if (lexer_expansion_process(lexer, &expansion) == LEX_EXP_ERR)
		return (LEX_EXP_ERR);
	ft_printf("Expansion processed : \n\tresult: %s\n", expansion.expansion);
	if (lexer_expansion_replace(&expansion, input) == LEX_EXP_ERR)
		return (LEX_EXP_ERR);
	// ft_printf("expansion processed res : %s\n", expansion.res->str);
	// ft_printf("expansion output : %s\n", *input);
	lexer->tok_len += ft_strlen(expansion.res->str);
	t_expansion_free(&expansion);
	return (LEX_EXP_OK);
	(void)input;
	(void)lexer;
}

/*
** lexer_expansion_replace:
**		Replace results of expansion in the original input string
*/
int			lexer_expansion_replace(t_expansion *expansion, char **input)
{
	*input = ft_strrep_free(*input, expansion->res->str, expansion->original, 1);
	if (!(*input))
		return (LEX_EXP_ERR);
	return (LEX_EXP_OK);
}
