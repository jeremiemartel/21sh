/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:40:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/24 14:53:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_parsing(t_lr_parser *parser)
{
	g_cfg = &parser->cfg; //todel : usefull for debug (yes it is a global)
	parser->ast_root = NULL;
	parser->cst_root = NULL;
	parser->states = NULL;
	if (init_context_free_grammar(&parser->cfg))
		return (1);
	if (sh_compute_lr_automata(parser))
		return (1);
	if (sh_compute_lr_tables(parser))
		return (1);
	return (0);
}
