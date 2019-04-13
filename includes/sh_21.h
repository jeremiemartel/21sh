/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 11:54:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

# include <stdarg.h>
# include "libft.h"
# include "sh_tokens.h"
# include "sh_grammar.h"
# include "sh_parser.h"
# include "sh_lexer.h"

/*
** index.c
*/
int		sh_index(t_symbol_id id);
/*
** t_expansion.c
*/
void		t_expansion_free(t_expansion *expansion);
void		t_expansion_show(t_expansion *exp);

#endif
