/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:40:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/07 23:40:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_parsing(t_lr_parser *parser)
{
	if (init_context_free_grammar(&parser->cfg))
		return (1);
	if (sh_compute_lr_automata(parser))
		return (1);
	sh_trim_non_kernels(parser);
	if (sh_compute_lr_tables(parser))
		return (1);
	return (0);
}
