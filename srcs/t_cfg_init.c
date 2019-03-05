/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cfg_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:17:10 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/05 20:02:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static	int (*g_init_productions[NB_NOTERMS])
	(t_symbol *symbol) = 
{
	t_cfg_init_productions_E,
	t_cfg_init_productions_OP,
	t_cfg_init_productions_EOL
};

int			t_cfg_init_productions_E(t_symbol *symbol)
{
	t_symbol_add_prod(symbol, 1, INT);
	t_symbol_add_prod(symbol, 5, OPN_PARENT, E, OP, E, CLS_PARENT);
	return (0);
}

int			t_cfg_init_productions_OP(t_symbol *symbol)
{
	t_symbol_add_prod(symbol, 1, PLUS);
	t_symbol_add_prod(symbol, 1, MULT);
	return (0);
}

int			t_cfg_init_productions_EOL(t_symbol *symbol)
{
	(void)symbol;
	return (0);
}

int			t_cfg_init_productions(t_cfg *cfg)
{
	int		i;

	i = NB_TERMS;
	while (i < NB_SYMBOLS)
	{
		g_init_productions[i - NB_TERMS](&(cfg->symbols[i]));
		i++;
	}
	return (0);
}

char		*t_cfg_init_symbol_get_value(int id)
{
	static char	*values[NB_SYMBOLS] = {
		"(",
		")",
		"+",
		"*",
		"INT",
		"ε",
		"OP",
		"\n",
		"$"
	};
	return (values[id]);
}

void		t_cfg_init_symbol(t_symbol *symbol, int id)
{
	symbol->id = id;
	symbol->productions = NULL;
	symbol->first_sets = NULL;
	ft_strcpy(symbol->value, t_cfg_init_symbol_get_value(id));
	return ;
}

t_cfg		*t_cfg_init(void)
{
	t_cfg	*cfg;
	int		i;

	if (!(cfg = malloc(sizeof(*cfg))))
		return (NULL);
	i = 0;
	while (i < NB_SYMBOLS)
	{
		t_cfg_init_symbol(&(cfg->symbols[i]), i);
		i++;
	}
	t_cfg_init_productions(cfg);
	return (cfg);
}
