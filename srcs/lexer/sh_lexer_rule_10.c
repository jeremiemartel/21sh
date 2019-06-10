/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_10.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:46:52 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 14:46:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule10(t_lexer *lexer)
{
	lexer->tok_len = 1;
	lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}
