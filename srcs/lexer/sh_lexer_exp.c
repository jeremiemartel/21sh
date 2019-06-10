/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:54:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 19:29:47 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp(t_lexer *lexer)
{
	char	*start;
	int		end;

	start = lexer->input + lexer->tok_start + lexer->tok_len;
	if (ft_strnstr(start, "${", 2))
		end = sh_expansions_parameter_detect(start) + 1;
	else if (start[0] == '$')
		end = sh_expansions_variable_detect(start);
	else if (start[0] == '~')
		end = sh_expansions_tilde_detect(start);
	else
		end = -1;
	if (end <= 0)
		// Call quote funtion !
		return (ft_perror_err("Expansion", "Wrong Format"));
	if (sh_verbose_expansion())
	{
		ft_dprintf(2, "expansion len : %d\n", end);
	}
	lexer->expansion = '$';
	lexer->tok_len += end;
	// ft_dprintf(2, "end : %d\n%c\n", end, lexer->input[lexer->tok_len + lexer->tok_start]);
	return (LEX_OK);
}
