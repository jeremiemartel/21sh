/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 17:13:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_prod(t_symbol *symbol, t_cfg *cfg, int nb_symbols, ...)
{
	va_list		ap;
	int			symbol_index;
	int 		i;
	static int	index = 0;

	if (ft_lstaddnew_ptr_last(&symbol->productions,
			&cfg->productions[index], sizeof(t_production *)))
		return (1);
	va_start(ap, nb_symbols);
	cfg->productions[index].symbols = NULL;
	cfg->productions[index].from = symbol;
	cfg->productions[index].index = index;
	i = 0;
	while (i < nb_symbols)
	{
		symbol_index = sh_index(va_arg(ap, int));
		if (ft_lstaddnew_ptr_last(&cfg->productions[index].symbols,
					&cfg->symbols[symbol_index], sizeof(t_symbol *)))
			return (1);
		i++;
	}
	index++;
	va_end(ap);
	return (0);
}

int		init_start_symbol(t_cfg *cfg, t_symbol *symbol)
{
	symbol->id = NB_SYMBOLS + 1;
	symbol->productions = NULL;
	sh_add_prod(symbol, cfg, 1, PROGRAM); //(1)
	ft_strcpy(symbol->debug, "S");
	return (0);
}

void	init_symbol(t_symbol *symbol, int index)
{
	int i;

	i = 0;
	while (i < NB_TERMS)
	{
		symbol->first_sets[i] = 0;
		symbol->follow_sets[i] = 0;
		i++;
	}
	symbol->productions = NULL;
	symbol->id = index;
	symbol->relevant = g_grammar[index].relevant;
	symbol->replacing = g_grammar[index].replacing;
	ft_strcpy(symbol->debug, g_grammar[index].debug);
}

int		init_context_free_grammar(t_cfg *cfg)
{
	int i;
	init_start_symbol(cfg, &cfg->start_symbol);
	i = 0;
	while (i < NB_SYMBOLS)
	{
		init_symbol(&cfg->symbols[i], i);
		i++;
	}
	i = NB_TERMS;
	while (i < NB_SYMBOLS)
	{
		if (g_grammar[i].init_prod(cfg, &cfg->symbols[i]))
			return (1);
		i++;
	}
	if (sh_compute_first_sets(cfg))
		return (1);
//	if (sh_compute_follow_sets(cfg))
//		return (1);
//	sh_print_cfg(cfg);
	return (0);
}
