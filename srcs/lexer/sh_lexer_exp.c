/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:54:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 14:10:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp(t_lexer *lexer)
{
	char	*start;
	int		end;

	start = lexer->input + lexer->tok_start + lexer->tok_len;
	if (ft_strnstr(start, "${", 2))
		end = sh_expansions_parameter_detect(start);
	else if (ft_strnstr(start, "$", 1))
		end = sh_expansions_variable_detect(start);
	else if (ft_strnstr(start, "~", 1))
		end = sh_expansions_tilde_detect(start);
	else
		end = -1;
	if (end == -1)
		// Call quote funtion !
		return (ft_perror_err("Expansion", "Wrong Format"));
	lexer->expansion = '$';
	lexer->tok_len += end;
	return (LEX_OK);
}
